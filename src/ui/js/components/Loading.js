/**
 * Displayed while Emscripten is loading
*/
const Loading = {
  render(root) {
    root.innerHTML = `<div id="loading">loading...</div>`;
  }
};
export default Loading;
