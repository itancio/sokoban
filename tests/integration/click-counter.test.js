const puppeteer = require("puppeteer");

const url = "http://localhost:8000/dist"; // TODO move to env

describe("click counter", () => {
  let browser;
  let page;
  
  beforeAll(async () => {
    browser = await puppeteer.launch({
      //args: ["--no-sandbox"],
      headless: true,
    });
  });
  beforeEach(async () => {
    page = await browser.newPage();
    await page.goto(url, {timeout: 35000});
    await page.waitForFunction(() => {
      const el = document.getElementById("status");
      return el && el.textContent.includes("Preparing");
    });
    await page.waitForFunction(() => {
      const el = document.getElementById("status");
      return el && !el.textContent.includes("Preparing");
    });
  });
  afterEach(async () => await page.close());
  afterAll(async () => await browser.close());
  
  it("should increment the counter on click", async () => {
    expect(await page.$eval("#click-output", e => e.textContent)).toContain("0");
    await page.click("#click-btn");
    expect(await page.$eval("#click-output", e => e.textContent)).toContain("1");
    await page.click("#click-btn");
    expect(await page.$eval("#click-output", e => e.textContent)).toContain("2");
  });
});

