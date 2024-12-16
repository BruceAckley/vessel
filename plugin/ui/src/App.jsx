import React from 'react';
import HamburgerMenu from './components/HamburgerMenu';
import ChordMap3D from './components/ChordMap';
import Dock from './components/Dock';

function App() {
    return (
        <>
            <HamburgerMenu />
            <main>
                <div className='chord-map-container'>
                    <ChordMap3D />
                </div>
                <Dock />
            </main>
        </>
    )
};

export default App
