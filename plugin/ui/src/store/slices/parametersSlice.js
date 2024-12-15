import { createSlice } from '@reduxjs/toolkit';

const parametersSlice = createSlice({
    name: 'parameters',
    initialState: {
        parameters: {},
    },
    reducers: {
        updateParameter: (state, action) => {
            state.parameters[action.payload.parameter] = action.payload.value;
        },
    },
});

export const {
    updateParameter,
} = parametersSlice.actions;

export default parametersSlice.reducer;
