const puppeteer = require("puppeteer");

const baseURL = "http://localhost:8000/dist";
jest.setTimeout(30000);

describe("index.html", () => {
  let browser;
  let page;

  beforeAll(async () => {
    browser = await puppeteer.launch({headless: true});
  });
  afterAll(() => browser.close());
  beforeEach(async () => {
    page = await browser.newPage();
    page.setDefaultTimeout(5000);
    page.setDefaultNavigationTimeout(30000);
  });
  afterEach(() => page.close());

  describe("home screen", () => {
    beforeEach(async () => {
      await page.goto(baseURL);
      await page.waitForSelector("#menu");
    });

    it("should have a title", async () => {
      expect(await page.$eval("h1", el => el.textContent)).toEqual("Sokoban");
    });

    it("should not show the game screen", async () => {
      expect(await page.$("#game")).toBeNull();
    });

    it("should load multiple levels", async () => {
      expect((await page.$$("a[href^='#']")).length).toBeGreaterThan(0);
    });

    it("should open the first level", async () => {
      const levelLinks = await page.$("a[href^='#']");
      await Promise.all([page.waitForNavigation(), levelLinks.click()]);
      expect(await page.url()).toMatch(/#1$/);
      expect(await page.$("#menu")).toBeNull();
      expect(await page.$("#game")).toBeTruthy();
    });
  });

  describe("game screen", () => {
    const playerPos = () =>
      page.$eval(".player, .player-on-goal", el => ({
        row: +el.getAttribute("data-row"),
        col: +el.getAttribute("data-col"),
      }))
    ;
    const squareAt = (row, col) => page.evaluateHandle(`
      document.querySelector('#board .cell[data-row="${row}"][data-col="${col}"]')`
    );

    beforeEach(async () => {
      // Tests assume test level 101 layout
      await page.goto(baseURL + "#101", {timeout: 30000});
      await page.waitForSelector("#game");
    });

    describe("change-level button", () => {
      it("should render", async () => {
        expect(await page.$("#change-level")).toBeTruthy();
      });

      it("should navigate back to the main menu when change-level is clicked", async () => {
        const homeBtn = await page.$("#change-level");
        expect(homeBtn).toBeTruthy();
        await Promise.all([page.waitForNavigation(), homeBtn.click()]);
        expect(await page.$("#game")).toBeNull();
        expect(await page.$("#menu")).not.toBeNull();
        expect(await page.url()).toMatch(/#$/);
      });
    });

    describe("controls", () => {
      it("should render", async () => {
        expect(await page.$("#controls")).toBeTruthy();
      });

      it("should render an undo button, disabled by default", async () => {
        const undoBtn = await page.$("#undo");
        expect(undoBtn).toBeTruthy();
        expect(await undoBtn.evaluate(el => el.disabled)).toBe(true);
      });

      it("should enable the undo button after a successful keyboard move", async () => {
        const undoBtn = await page.$("#undo");
        expect(undoBtn).toBeTruthy();
        await page.keyboard.press("ArrowRight");
        expect(await undoBtn.evaluate(el => el.disabled)).toBe(false);
      });

      it("should enable the undo button after a successful mouse move", async () => {
        const undoBtn = await page.$("#undo");
        expect(undoBtn).toBeTruthy();
        await (await squareAt(4, 3)).click();
        expect(await undoBtn.evaluate(el => el.disabled)).toBe(false);
      });

      it("should render a reset button, disabled by default", async () => {
        const resetBtn = await page.$("#reset");
        expect(resetBtn).toBeTruthy();
        expect(await resetBtn.evaluate(el => el.disabled)).toBe(true);
      });

      it("should enable the reset button after a successful keyboard move", async () => {
        const resetBtn = await page.$("#reset");
        expect(resetBtn).toBeTruthy();
        await page.keyboard.press("ArrowRight");
        expect(await resetBtn.evaluate(el => el.disabled)).toBe(false);
      });

      it("should enable the reset button after a successful mouse move", async () => {
        const resetBtn = await page.$("#reset");
        expect(resetBtn).toBeTruthy();
        await (await squareAt(4, 3)).click();
        expect(await resetBtn.evaluate(el => el.disabled)).toBe(false);
      });
    });

    describe("board", () => {
      it("should render", async () => {
        expect(await page.$("#board")).toBeTruthy();
      });

      it("should have a single player cell", async () => {
        expect(await page.$$(".player, .player-on-goal")).toHaveLength(1);
      });

      it("should allow the player to move right via arrow key on empty floor", async () => {
        const {col: preX} = await playerPos();
        await page.keyboard.press("ArrowRight");
        const {col: postX} = await playerPos();
        expect(postX - 1).toEqual(preX);
      });

      it("should allow the player to move left via arrow key on empty floor", async () => {
        await page.keyboard.press("ArrowRight");
        const {col: preX} = await playerPos();
        await page.keyboard.press("ArrowLeft");
        const {col: postX} = await playerPos();
        expect(postX + 1).toEqual(preX);
      });

      it("should allow the player to move up via arrow key on empty floor", async () => {
        const {row: preY} = await playerPos();
        await page.keyboard.press("ArrowUp");
        const {row: postY} = await playerPos();
        expect(postY + 1).toEqual(preY);
      });

      it("should allow the player to move down via arrow key on empty floor", async () => {
        const {row: preY} = await playerPos();
        await page.keyboard.press("ArrowDown");
        const {row: postY} = await playerPos();
        expect(postY - 1).toEqual(preY);
      });

      it("should allow click-move on empty floor", async () => {
        const {row: preY, col: preX} = await playerPos();
        await (await squareAt(preY - 2, preX + 1)).click();
        const {row: postY, col: postX} = await playerPos();
        expect(postY).toEqual(preY - 2);
        expect(postX).toEqual(preX + 1);
      });

      it("should allow click-move onto a box", async () => {
        const cellClassPrePush = await (await squareAt(2, 1))
          .evaluate(el => el.className);
        expect(cellClassPrePush).toMatch(/\bbox\b/);
        await (await squareAt(3, 1)).click();
        const {row, col} = await playerPos();
        expect(row).toEqual(3);
        expect(col).toEqual(1);
        await (await squareAt(2, 1)).click();
        const {
          row: rowAfterPush, col: colAfterPush
        } = await playerPos();
        expect(rowAfterPush).toEqual(2);
        expect(colAfterPush).toEqual(1);
        const cellClassPostPush = await (await squareAt(1, 1))
          .evaluate(el => el.className);
        expect(cellClassPostPush).toMatch(/\bbox-on-goal\b/);
      });

      it("should allow the test level to be completed", async () => {
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 0");
        await (await squareAt(6, 7)).click();
        await page.keyboard.press("ArrowDown");
        await page.keyboard.press("ArrowDown");
        await page.keyboard.press("ArrowLeft");
        await page.keyboard.press("ArrowUp");
        await page.keyboard.press("ArrowUp");
        await page.keyboard.press("ArrowUp");
        await page.keyboard.press("ArrowUp");
        await page.keyboard.press("ArrowUp");
        await (await squareAt(3, 1)).click();
        await page.keyboard.press("ArrowUp");
        await (await squareAt(2, 5)).click();
        await page.keyboard.press("ArrowRight");
        await page.keyboard.press("ArrowRight");
        await (await squareAt(3, 8)).click();
        await page.keyboard.press("ArrowUp");
        await (await squareAt(6, 5)).click();
        await page.keyboard.press("ArrowDown");
        await (await squareAt(8, 6)).click();
        await page.keyboard.press("ArrowLeft");
        await page.keyboard.press("ArrowLeft");
        await page.keyboard.press("ArrowLeft");
        await page.keyboard.press("ArrowLeft");
        await (await squareAt(7, 1)).click();
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 47");
        await page.keyboard.press("ArrowDown");
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Solved in 48 moves");
      });
    });

    describe("status", () => {
      it("should render", async () => {
        expect(await page.$("#status")).toBeTruthy();
      });

      it("should start with 0 moves", async () => {
        expect(await page.$eval("#status", el => el.textContent)).toMatch(/Moves: 0\b/i);
      });

      it("should increment moves as they are performed", async () => {
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 0");
        await page.keyboard.press("ArrowDown");
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 1");
        await page.keyboard.press("ArrowUp");
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 2");
      });

      it("shouldn't increment moves when moving into a wall", async () => {
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 0");
        await page.keyboard.press("ArrowLeft");
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 1");
        await page.keyboard.press("ArrowLeft");
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 1");
      });

      it("should increment multiple times for a click-move", async () => {
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 0");
        await (await squareAt(4, 3)).click();
        expect(await page.$eval("#status", el => el.textContent.trim()))
          .toEqual("Moves: 4");
      });
    });
  });
});

