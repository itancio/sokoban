const puppeteer = require("puppeteer");

const baseURL = "http://localhost:8001/dist";
jest.setTimeout(9000);

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
    page.setDefaultNavigationTimeout(10000);
  });
  afterEach(async () => await page.close());

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

    beforeEach(async () => {
      await page.goto(baseURL + "#1", {timeout: 30000});
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
    });

    describe("board", () => {
      it("should render", async () => {
        expect(await page.$("#board")).toBeTruthy();
      });

      it("should have a single player cell", async () => {
        expect(await page.$$(".player, .player-on-goal")).toHaveLength(1);
      });

      it("should allow the player to move right via arrow key", async () => {
        const {col: preX} = await playerPos();
        await page.keyboard.press("ArrowRight");
        const {col: postX} = await playerPos();
        expect(postX - 1).toEqual(preX);
      });

      it("should allow the player to move left via arrow key", async () => {
        await page.keyboard.press("ArrowRight");
        const {col: preX} = await playerPos();
        await page.keyboard.press("ArrowLeft");
        const {col: postX} = await playerPos();
        expect(postX + 1).toEqual(preX);
      });
    });
  });
});

