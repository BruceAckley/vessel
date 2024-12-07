import { createSlice } from '@reduxjs/toolkit';

const previewedChordSlice = createSlice({
    name: 'previewedChord',
    initialState: {
        previewedChord: null,
    },
    reducers: {
        previewChord: (state, action) => {
            state.previewedChord = action.payload.chord;
        },
    },
});

export const {
    previewChord,
} = previewedChordSlice.actions;

export default previewedChordSlice.reducer;
