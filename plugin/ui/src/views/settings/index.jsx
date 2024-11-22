import { React } from "react";

import { JuceComboBox } from "../../components/JuceComboBox";


export const Settings = () => {
    return (
        <div>
            <h1>Settings</h1>
            <h2>Tonal Center: </h2>
            <JuceComboBox identifier="tonalCenter" />
        </div>
    );
}