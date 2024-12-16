import React, { useState } from 'react';
import '../styles/Dock.css';

const Dock = () => {
    const [cards, setCards] = useState([]);

    const keys = [
        { note: 'C', type: 'white' },
        { note: 'C#', type: 'black' },
        { note: 'D', type: 'white' },
        { note: 'D#', type: 'black' },
        { note: 'E', type: 'white' },
        { note: 'F', type: 'white' },
        { note: 'F#', type: 'black' },
        { note: 'G', type: 'white' },
        { note: 'G#', type: 'black' },
        { note: 'A', type: 'white' },
        { note: 'A#', type: 'black' },
        { note: 'B', type: 'white' },
    ];

    const handleKeyClick = (note) => {
        const chord = prompt(`Enter chord for ${note}:`);
        if (chord) {
            setCards((prevCards) => [
                ...prevCards.filter((card) => card.note !== note),
                { note, chord },
            ]);
        }
    };

    const getChordForKey = (note) => {
        const card = cards.find((card) => card.note === note);
        return card ? card.chord : '';
    };

    return (
        <div className="piano-octave">
            {keys.map((key, index) => (
                <div
                    key={index}
                    className={`key ${key.type}`}
                    onClick={() => handleKeyClick(key.note)}
                >
                    <span className="note-label">{key.note}</span>
                    <span className="chord-label">{getChordForKey(key.note)}</span>
                </div>
            ))}
        </div>
    );
};

export default Dock;
