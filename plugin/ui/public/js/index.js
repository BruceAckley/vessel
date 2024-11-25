import * as Juce from "./juce/index.js";

console.log("JUCE frontend library successfully imported");

window.__JUCE__.backend.addEventListener(
  "exampleEvent",
  (objectFromBackend) => {
    console.log(objectFromBackend);
  }
);

const data = window.__JUCE__.initialisationData;

document.getElementById("pluginVersion").innerText = data.pluginVersion;

// Main
document.addEventListener("DOMContentLoaded", () => {
  const tonalCenterComboBox = document.getElementById(
    "tonalCenterComboBox"
  );
  const tonalCenterComboBoxState = Juce.getComboBoxState(
    "tonalCenterComboBox"
  );
  tonalCenterComboBoxState.propertiesChangedEvent.addListener(() => {
    tonalCenterComboBoxState.properties.choices.forEach((choice) => {
      tonalCenterComboBox.innerHTML += `<option value=\"${choice}\">${choice}</option>`;
    });
  });
  tonalCenterComboBoxState.valueChangedEvent.addListener(() => {
    tonalCenterComboBox.selectedIndex =
      tonalCenterComboBoxState.getChoiceIndex();
  });
  tonalCenterComboBox.oninput = function () {
    tonalCenterComboBoxState.setChoiceIndex(this.selectedIndex);
  };
});
