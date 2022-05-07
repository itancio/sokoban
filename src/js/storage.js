const storage = {
  initialize() {
    if (!localStorage.getItem("sokoban")) {
      localStorage.setItem("sokoban", JSON.stringify({levels: []}));
    }
  },
  bestScore(level) {
    const data = JSON.parse(localStorage.getItem("sokoban"));
    return data.levels[level] ? data.levels[level].bestScore : undefined;
  },
  saveBestScore(level, score) {
    const data = JSON.parse(localStorage.getItem("sokoban"));
    data.levels[level] = {
      ...data.levels[level],
      bestScore: data.levels[level]
        ? Math.min(data.levels[level].bestScore, score) : score
    };
    localStorage.setItem("sokoban", JSON.stringify(data));
  },
};
storage.initialize();
export default storage;
