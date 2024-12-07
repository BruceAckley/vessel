import { createSlice } from '@reduxjs/toolkit';

const dockSlice = createSlice({
    name: 'dock',
    initialState: {
        dock: [],
    },
    reducers: {
        addChordToDock: (state, action) => {
            state.dock.push(action.payload);
        },
        removeChordFromDock: (state, action) => {
            state.dock = state.dock.filter(chord => chord !== action.payload);
        },
        reorderDock: (state, action) => {
            state.dock = action.payload.newDockOrder;
        },
    },
});

export const {
    addChordToDock,
    removeChordFromDock,
    reorderDock,
} = dockSlice.actions;

export default dockSlice.reducer;
