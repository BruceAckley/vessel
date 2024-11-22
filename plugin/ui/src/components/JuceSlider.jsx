import "@fontsource/roboto/300.css";
import "@fontsource/roboto/400.css";
import "@fontsource/roboto/500.css";
import "@fontsource/roboto/700.css";

import Box from "@mui/material/Container";
import Typography from "@mui/material/Typography";
import Slider from "@mui/material/Slider";

import { React, useState, useEffect } from "react";
import PropTypes from "prop-types";

import * as Juce from "juce-framework-frontend";

import "./App.css";


export function JuceSlider({ identifier, title }) {
    JuceSlider.propTypes = {
      identifier: PropTypes.string,
      title: PropTypes.string,
    };
  
    const sliderState = Juce.getSliderState(identifier);
  
    const [value, setValue] = useState(sliderState.getNormalisedValue());
    const [properties, setProperties] = useState(sliderState.properties);
  
    const handleChange = (event, newValue) => {
      sliderState.setNormalisedValue(newValue);
      setValue(newValue);
    };
  
    const mouseDown = () => {
      sliderState.sliderDragStarted();
    };
  
    const changeCommitted = (event, newValue) => {
      sliderState.setNormalisedValue(newValue);
      sliderState.sliderDragEnded();
    };
  
    useEffect(() => {
      const valueListenerId = sliderState.valueChangedEvent.addListener(() => {
        setValue(sliderState.getNormalisedValue());
      });
      const propertiesListenerId = sliderState.propertiesChangedEvent.addListener(
        () => setProperties(sliderState.properties)
      );
  
      return function cleanup() {
        sliderState.valueChangedEvent.removeListener(valueListenerId);
        sliderState.propertiesChangedEvent.removeListener(propertiesListenerId);
      };
    });
  
    function calculateValue() {
      return sliderState.getScaledValue();
    }
  
    return (
      <Box
        {...{
          [controlParameterIndexAnnotation]:
            sliderState.properties.parameterIndex,
        }}
      >
        <Typography sx={{ mt: 1.5 }}>
          {properties.name}: {sliderState.getScaledValue()} {properties.label}
        </Typography>
        <Slider
          aria-label={title}
          value={value}
          scale={calculateValue}
          onChange={handleChange}
          min={0}
          max={1}
          step={1 / (properties.numSteps - 1)}
          onChangeCommitted={changeCommitted}
          onMouseDown={mouseDown}
        />
      </Box>
    );
  }
  