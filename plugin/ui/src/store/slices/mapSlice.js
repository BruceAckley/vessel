import { createSlice } from '@reduxjs/toolkit';

const mapSlice = createSlice({
    name: 'map',
    initialState: {
        chordMap: {},
    },
    reducers: {
        fetchChordMap: (state, action) => {
            // TODO: fetch chord map from backend
        },
    },
});

export const {
    fetchChordMap,
} = mapSlice.actions;

export default mapSlice.reducer;
