import React, { useEffect, useRef } from 'react';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls';
import { initScene, placeNode } from '../utils/threeUtils';
import '../styles/ChordMap.css';

const ChordMap3D = () => {
    const mountRef = useRef(null);
    const sceneRef = useRef(null);
    const rendererRef = useRef(null);
    const cameraRef = useRef(null);
    const controlsRef = useRef(null);

    useEffect(() => {
        const { scene, camera, renderer } = initScene(mountRef.current);
        sceneRef.current = scene;
        cameraRef.current = camera;
        rendererRef.current = renderer;

        const controls = new OrbitControls(camera, renderer.domElement);
        controlsRef.current = controls;

        const chordRelationships = {
            'C': { x: 0, y: 0, z: 0, related: ['F', 'G', 'Am'] },
            'F': { x: -2, y: 1, z: 2, related: ['Bb', 'C', 'Dm'] },
            // TODO: Connect to JUCE chord map
        };

        Object.entries(chordRelationships).forEach(([chord, position]) => {
            const node = placeNode(position.x, position.y, position.z, chord);
            sceneRef.current.add(node);
        });

        const animate = () => {
            requestAnimationFrame(animate);
            controls.update();
            renderer.render(scene, camera);
        };
        animate();

        return () => {
            mountRef.current?.removeChild(renderer.domElement);
            scene.clear();
        };
    }, []);

    return <div ref={mountRef} style={{ width: '100%', height: '100%' }} />;
};

export default ChordMap3D;
