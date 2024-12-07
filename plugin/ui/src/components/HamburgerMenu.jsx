/* 
* Implements the sliding preferences menu
*
* Methods:
* - initMenu: Initializes the menu
* - toggleVisible: Expands or collapses the menu
* - setTonalCenter: Hanldes the tonal center selection
* - setMapMode: Handles the map mode selection
* - setMood: Handles the mood selection
* - setVoiceLeading: Handles the voice leading selection
* - setPassingTones: Handles the passing tones selection
* - saveDock: save the current dock to the user's preferences
* - loadDock: load the user's preferences
* - resetDock: reset the dock to the default state
* - exportDock: export the dock to a file
*/

import React, { useState, useRef, useEffect } from 'react';
import '../styles/HamburgerMenu.css';

const HamburgerMenu = () => {
    const [isOpen, setIsOpen] = useState(false);
    const menuRef = useRef(null);

    useEffect(() => {
        const handleClickOutside = (event) => {
            if (menuRef.current && !menuRef.current.contains(event.target)) {
                setIsOpen(false);
            }
        };

        document.addEventListener('mousedown', handleClickOutside);
        return () => {
            document.removeEventListener('mousedown', handleClickOutside);
        };
    }, []);

    return (
        <div ref={menuRef}>
            <button
                className={`hamburger-menu-button ${isOpen ? 'open' : ''}`}
                onClick={() => setIsOpen(!isOpen)}
                aria-label="Toggle settings menu"
            >
                <span></span>
                <span></span>
                <span></span>
            </button>

            <nav className={`hamburger-menu ${isOpen ? 'open' : ''}`}>
                <ul>
                    <li>
                        TODO: Add tonal center selector here
                    </li>
                </ul>
            </nav>
        </div>
    );
};

export default HamburgerMenu;
