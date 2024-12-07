import { configureStore } from "@reduxjs/toolkit";
import * as types from './actionTypes';
import dockReducer from './slices/dockSlice';
import mapReducer from './slices/mapSlice';
import parametersReducer from './slices/parametersSlice';
import previewChordReducer from './slices/previewedChordSlice';

const juceMiddleware = store => next => action => {
    if (action.type === types.FETCH_CHORD_MAP) {
        window.JUCE?.fetchChordMap(action.payload);
    }
    if (action.type === types.ADD_CHORD_TO_DOCK) {
        window.JUCE?.addChordToDock(action.payload);
    }
    if (action.type === type.REMOVE_CHORD_FROM_DOCK) {
        window.JUCE?.removeChordFromDock(action.payload);
    }
    if (action.type == types.REORDER_DOCK) {
        window.JUCE?.reorderDock(action.payload);
    }
    if (action.type === types.UPDATE_PARAMETER) {
        window.JUCE?.updateParameter(action.payload);
    }
    if (action.type === types.PREVIEW_CHORD) {
        window.JUCE?.previewChord(action.payload);
    }
};

export const store = configureStore({
    reducer: {
        dock: dockReducer,
        map: mapReducer,
        parameters: parametersReducer,
        previewChord: previewChordReducer,
    },
    middleware: (getDefaultMiddleware) => 
        getDefaultMiddleware().concat(juceMiddleware)
});
