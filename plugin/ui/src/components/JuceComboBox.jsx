import "@fontsource/roboto/300.css";
import "@fontsource/roboto/400.css";
import "@fontsource/roboto/500.css";
import "@fontsource/roboto/700.css";

import Box from "@mui/material/Container";
import InputLabel from "@mui/material/InputLabel";
import MenuItem from "@mui/material/MenuItem";
import FormControl from "@mui/material/FormControl";
import Select from "@mui/material/Select";

import { React, useState, useEffect } from "react";
import PropTypes from "prop-types";

import * as Juce from "juce-framework-frontend";

import "../App.css";


const controlParameterIndexAnnotation = "controlparameterindex";

export function JuceComboBox({ identifier }) {
    JuceComboBox.propTypes = {
        identifier: PropTypes.string,
    };

    const comboBoxState = Juce.getComboBoxState(identifier);

    const [value, setValue] = useState(comboBoxState.getChoiceIndex());
    const [properties, setProperties] = useState(comboBoxState.properties);

    const handleChange = (event) => {
        comboBoxState.setChoiceIndex(event.target.value);
        setValue(event.target.value);
    };

    useEffect(() => {
        const valueListenerId = comboBoxState.valueChangedEvent.addListener(() => {
            setValue(comboBoxState.getChoiceIndex());
        });
        const propertiesListenerId =
            comboBoxState.propertiesChangedEvent.addListener(() => {
                setProperties(comboBoxState.properties);
            });

        return function cleanup() {
            comboBoxState.valueChangedEvent.removeListener(valueListenerId);
            comboBoxState.propertiesChangedEvent.removeListener(propertiesListenerId);
        };
    });

    return (
        <Box
            {...{
                [controlParameterIndexAnnotation]:
                    comboBoxState.properties.parameterIndex,
            }}
        >
            <FormControl fullWidth>
                <InputLabel id={identifier}>{properties.name}</InputLabel>
                <Select
                    labelId={identifier}
                    value={value}
                    label={properties.name}
                    onChange={handleChange}
                >
                    {properties.choices.map((choice, i) => (
                        <MenuItem value={i} key={i}>
                            {choice}
                        </MenuItem>
                    ))}
                </Select>
            </FormControl>
        </Box>
    );
}
