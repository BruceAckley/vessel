import * as THREE from 'three';


export const initScene = (mountElement) => {
    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(
        75,
        mountElement.clientWidth / mountElement.clientHeight,
        0.1,
        1000
    );
    
    const renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(mountElement.clientWidth, mountElement.clientHeight);
    mountElement.appendChild(renderer.domElement);
    
    camera.position.z = 5;
    scene.background = new THREE.Color(0x000000);
    
    return { scene, camera, renderer };
};

export const placeNode = (x, y, z, label) => {
    const geometry = new THREE.SphereGeometry(0.2, 32, 32);
    const material = new THREE.MeshPhongMaterial({ color: 0xffffff });
    const sphere = new THREE.Mesh(geometry, material);
    
    sphere.position.set(x, y, z);
    sphere.userData.label = label;
    
    return sphere;
};
