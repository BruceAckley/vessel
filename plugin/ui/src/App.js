import "@fontsource/roboto/300.css";
import "@fontsource/roboto/400.css";
import "@fontsource/roboto/500.css";
import "@fontsource/roboto/700.css";

import { React } from "react";

import * as Juce from "juce-framework-frontend";

import { Settings } from "./views/settings";
import "./App.css";


// Custom attributes in React must be in all lower case
const controlParameterIndexAnnotation = "controlparameterindex";

function App() {
  const controlParameterIndexUpdater = new Juce.ControlParameterIndexUpdater(
    controlParameterIndexAnnotation
  );

  document.addEventListener("mousemove", (event) => {
    controlParameterIndexUpdater.handleMouseMove(event);
  });

  console.log(window.__JUCE__.backend);

  return (
    <div>
      <Settings />
    </div>
  );
}

export default App;
