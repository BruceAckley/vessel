import React from 'react';
import '../styles/ChordCard.css';

const ChordCard = ({ note, chord, type }) => {
    return (
        <div className={`chord-card ${type}`}>
            <span className="note-label">{note}</span>
            <span className="chord-label">{chord}</span>
        </div>  
    );
};

export default ChordCard;
