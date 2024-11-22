import "@fontsource/roboto/300.css";
import "@fontsource/roboto/400.css";
import "@fontsource/roboto/500.css";
import "@fontsource/roboto/700.css";

import Box from "@mui/material/Container";
import Checkbox from "@mui/material/Checkbox";
import FormGroup from "@mui/material/FormGroup";
import FormControlLabel from "@mui/material/FormControlLabel";

import { React, useState, useEffect } from "react";
import PropTypes from "prop-types";

import * as Juce from "juce-framework-frontend";

import "./App.css";


export function JuceCheckbox({ identifier }) {
    JuceCheckbox.propTypes = {
      identifier: PropTypes.string,
    };
  
    const checkboxState = Juce.getToggleState(identifier);
  
    const [value, setValue] = useState(checkboxState.getValue());
    const [properties, setProperties] = useState(checkboxState.properties);
  
    const handleChange = (event) => {
      checkboxState.setValue(event.target.checked);
      setValue(event.target.checked);
    };
  
    useEffect(() => {
      const valueListenerId = checkboxState.valueChangedEvent.addListener(() => {
        setValue(checkboxState.getValue());
      });
      const propertiesListenerId =
        checkboxState.propertiesChangedEvent.addListener(() =>
          setProperties(checkboxState.properties)
        );
  
      return function cleanup() {
        checkboxState.valueChangedEvent.removeListener(valueListenerId);
        checkboxState.propertiesChangedEvent.removeListener(propertiesListenerId);
      };
    });
  
    const cb = <Checkbox checked={value} onChange={handleChange} />;
  
    return (
      <Box
        {...{
          [controlParameterIndexAnnotation]:
            checkboxState.properties.parameterIndex,
        }}
      >
        <FormGroup>
          <FormControlLabel control={cb} label={properties.name} />
        </FormGroup>
      </Box>
    );
  }
  