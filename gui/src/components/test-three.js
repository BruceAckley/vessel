// import React from 'react';
// import * as THREE from 'three';
// import { PointerLockControls } from 'three/examples/jsm/controls/PointerLockControls';


// class TestThree extends React.Component {
//     componentDidMount() {
//         var scene = new THREE.Scene();
//         var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
//         var renderer = new THREE.WebGLRenderer();
//         renderer.setSize(window.innerWidth, window.innerHeight);
//         document.body.appendChild(renderer.domElement);

//         var controls = new PointerLockControls(camera, document.body);

//         var geometry = new THREE.SphereGeometry(1, 32, 32);
//         var material = new THREE.MeshBasicMaterial({ color: 0x333333 });
//         var sphere = new THREE.Mesh(geometry, material);
//         scene.add(sphere);

//         camera.position.z = 5;

//         var animate = function () {
//             requestAnimationFrame(animate);

//             renderer.render(scene, camera);
//         };

//         animate();

//         document.addEventListener('click', () => {
//             controls.lock();
//         });

//         controls.addEventListener('lock', () => {
//             document.addEventListener('mousemove', onMouseMove, false);
//             document.addEventListener('mousedown', onMouseDown, false);
//         });

//         controls.addEventListener('unlock', () => {
//             document.removeEventListener('mousemove', onMouseMove, false);
//             document.removeEventListener('mousedown', onMouseDown, false);
//         });

//         function onMouseMove(event) {
//             const movementX = event.movementX || event.mozMovementX || event.webkitMovementX || 0;
//             const movementY = event.movementY || event.mozMovementY || event.webkitMovementY || 0;

//             controls.object.rotation.y -= movementX * 0.002;
//             controls.object.rotation.x -= movementY * 0.002;
//             controls.object.rotation.x = Math.max(-Math.PI / 2, Math.min(Math.PI / 2, controls.getObject().rotation.x));
//         }

//         function onMouseDown() {
//             if (controls.isLocked) {
//                 controls.moveForward(1);
//             }
//         }
//     }

//     render() {
//         return (
//             <canvas id="c"></canvas>
//         );
//     }
// }

// export default TestThree;


import React from 'react';
import * as THREE from 'three';
import { PointerLockControls } from 'three/examples/jsm/controls/PointerLockControls';

class TestThree extends React.Component {
    componentDidMount() {
        var scene = new THREE.Scene();
        var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        var renderer = new THREE.WebGLRenderer();
        renderer.setSize(window.innerWidth, window.innerHeight);
        document.body.appendChild(renderer.domElement);

        var controls = new PointerLockControls(camera, document.body);

        var geometry = new THREE.SphereGeometry(1, 32, 32);
        const material = new THREE.MeshPhongMaterial({color: 0x44aa88});  // greenish blue
        var sphere = new THREE.Mesh(geometry, material);
        scene.add(sphere);

        const color = 0xFFFFFF;
        const intensity = 3;
        const light = new THREE.DirectionalLight(color, intensity);
        light.position.set(-1, 2, 7);
        scene.add(light);

        // Create a canvas and draw text on it
        var canvas = document.createElement('canvas');
        var context = canvas.getContext('2d');
        context.font = '48px Arial';
        context.fillStyle = 'white';
        context.fillText('Hello', 0, 50);

        // Create a texture from the canvas
        var texture = new THREE.CanvasTexture(canvas);

        // Create a sprite material using the texture
        var spriteMaterial = new THREE.SpriteMaterial({ map: texture });

        // Create a sprite and add it to the scene
        var sprite = new THREE.Sprite(spriteMaterial);
        sprite.scale.set(2, 1, 1); // Adjust the scale if needed
        scene.add(sprite);

        camera.position.z = 5;

        var animate = function () {
            requestAnimationFrame(animate);

            // Make the sprite always face the camera
            sprite.position.copy(sphere.position);
            sprite.position.y += 1.5; // Adjust the position if needed
            sprite.lookAt(camera.position);

            renderer.render(scene, camera);
        };

        animate();

        document.addEventListener('click', () => {
            controls.lock();
        });

        controls.addEventListener('lock', () => {
            document.addEventListener('mousemove', onMouseMove, false);
            document.addEventListener('mousedown', onMouseDown, false);
        });

        controls.addEventListener('unlock', () => {
            document.removeEventListener('mousemove', onMouseMove, false);
            document.removeEventListener('mousedown', onMouseDown, false);
        });

        function onMouseMove(event) {
            const movementX = event.movementX || event.mozMovementX || event.webkitMovementX || 0;
            const movementY = event.movementY || event.mozMovementY || event.webkitMovementY || 0;

            controls.object.rotation.y -= movementX * 0.002;
            controls.object.rotation.x -= movementY * 0.002;
            controls.getObject().rotation.x = Math.max(-Math.PI / 2, Math.min(Math.PI / 2, controls.getObject().rotation.x));
        }

        function onMouseDown() {
            if (controls.isLocked) {
                controls.moveForward(1);
            }
        }
    }

    render() {
        return (
            <canvas id="c"></canvas>
        );
    }
}

export default TestThree;