/**
 * This module provides getters and setters for managing persistent local storage
*/
const storage = {

  /**
   * Set up the localStorage JSON if needed. Must be called before other methods.
  */
  initialize() {
    if (!localStorage.getItem("sokoban")) {
      localStorage.setItem("sokoban", JSON.stringify({levels: []}));
    }
  },

  /**
   * Get the best score for a level
   * @param level number the level number
   * @return number the best score for level number level
  */
  bestScore(level) {
    const data = JSON.parse(localStorage.getItem("sokoban"));
    return data.levels[level] ? data.levels[level].bestScore : undefined;
  },

  /**
   * Stores the best score for a level, if better than the existing score
   * @param level number the level number
   * @param score number the score
  */
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
