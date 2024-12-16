import React, { useState } from 'react';

function Tooltip({ title, description, children }) {
  const [isVisible, setIsVisible] = useState(false);

  const showTooltip = () => {
    setIsVisible(true);
  };

  const hideTooltip = () => {
    setIsVisible(false);
  };

  return (
    <div
      className="tooltip-container"
      onMouseEnter={showTooltip}
      onMouseLeave={hideTooltip}
    >
      {children}
      {isVisible && (
        <div className="tooltip-content">
          <h3 className="tooltip-title">{title}</h3>
          <p className="tooltip-description">{description}</p>
        </div>
      )}
    </div>
  );
}

export default Tooltip;
