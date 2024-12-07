Left off at 19:50  here: https://www.youtube.com/watch?v=tgf6J8foCiw

TODO: Add to trello: https://trello.com/b/QHGCGMTr/vessel-tonal-harmony
- Black keys are fifths, like Nopia (double check how that was presented)
     - Chord being played is displayed in plugin
     - Notes making up the chord being played are displayed
     - Dissonance level is shown (based on tonic, subdominant, or dominant)
     - Recommended next chords (based on connections) are shown, along with the key on the keyboard to use for that chord

TODO: Ideas from Bryce
If we can read the length and position in the clip (timing), 
     - Suggest passing notes or embelishments
     - For current chord, other chords it could be replaced with
     - For current chord, other chords that could come after
     - Like MS Word Clippy for music - "Hey! I noticed this chord sounds like shit. Have you considered this one?"

     - Filter chords by instrument! Guitar chords vs piano chords (range is bigger on piano than guitar) vs bass arpeggios

3D explorer
Secondary functions

Buy this for inspiration:
https://www.youtube.com/watch?v=buIpYXq80_Q&list=PLt-Oh3MSFwB8mfyRvS0YGpLpSW8t4ci_0

# THREEJS

Use ThreeJS TextGeometry primitive: https://threejs.org/manual/#en/primitives#Diagram-TextGeometry
This could draw chord names

Use ThreeJS Picking for clicking: https://threejs.org/manual/#en/picking

Manual ThreeJS https://threejs.org/manual/#en/tips#tabindex

O_O Flying: https://threejs.org/docs/index.html#examples/en/controls/FlyControls
Example: https://threejs.org/examples/misc_controls_fly.html

https://github.com/JanWilczek/juce-webview-tutorial/blob/main/plugin/ui/public/js/index.js

# WINDOWS WEBVIEW

When developing a plugin that uses WebView2, you need to ensure that the WebView2 runtime is available on the target Windows machines where your plugin will run. WebView2 does not get statically linked into your application; instead, it relies on the WebView2 runtime being installed on the user's machine.

Here are your options:

Ensure WebView2 Runtime is Installed: You can check for the WebView2 runtime on the user's machine and prompt them to install it if it's not present. Microsoft provides a bootstrapper that can be used to install the runtime.

Distribute the Evergreen Standalone Installer: You can include the WebView2 Evergreen Standalone Installer with your application, which will install the runtime if it's not already present.

Use Fixed Version Distribution: You can package a specific version of the WebView2 runtime with your application. This ensures that your application uses the exact version of the runtime you tested with, but it increases the size of your application.

To summarize, you need to ensure that the WebView2 runtime is available on the Windows machines where your plugin will run. It is not statically linked into your application, so you cannot compile it on Mac or Linux and expect it to work without the runtime on Windows.
