import React, { useState, useRef, useEffect, useId } from 'react';
import '../styles/HamburgerMenu.css';
import * as Juce from "../../juce/index.js";

const HamburgerMenu = () => {
    const [isOpen, setIsOpen] = useState(false);
    const menuRef = useRef(null);
    const tonalCenterSelectId = useId();
    const [tonalCenterOptions, setTonalCenterOptions] = useState([]);
    const [selectedTonalCenter, setSelectedTonalCenter] = useState('');

    useEffect(() => {
        const handleClickOutside = (event) => {
            if (menuRef.current && !menuRef.current.contains(event.target)) {
                setIsOpen(false);
            }
        };

        document.addEventListener('mousedown', handleClickOutside);

        const tonalCenterComboBoxState = Juce.getComboBoxState('tonalCenterComboBox');

        tonalCenterComboBoxState.propertiesChangedEvent.addListener(() => {
            setTonalCenterOptions(tonalCenterComboBoxState.properties.choices);
        });

        tonalCenterComboBoxState.valueChangedEvent.addListener(() => {
            setSelectedTonalCenter(tonalCenterComboBoxState.getChoiceIndex());
            tonalCenterComboBoxState.propertiesChangedEvent.removeListener();
            tonalCenterComboBoxState.valueChangedEvent.removeListener();
        });

        return () => {
            document.removeEventListener('mousedown', handleClickOutside);
        };
    }, []);

    const handleTonalCenterChange = (event) => {
        const index = event.target.selectedIndex;
        setSelectedTonalCenter(index);
        const tonalCenterComboBoxState = Juce.getComboBoxState('tonalCenterComboBox');
        tonalCenterComboBoxState.setChoiceIndex(index);
    };

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
                    <li className='list-item'>
                        <label htmlFor={tonalCenterSelectId}>
                            Select tonal center (key):
                        </label>
                        <select
                            id={tonalCenterSelectId}
                            className="select"
                            value={selectedTonalCenter}
                            onChange={handleTonalCenterChange}
                        >
                            <option></option>
                            {tonalCenterOptions.map((option, index) => (
                                <option key={index} value={option}>
                                    {option}
                                </option>
                            ))}
                        </select>
                    </li>
                </ul>
            </nav>
        </div>
    );
};

export default HamburgerMenu;
