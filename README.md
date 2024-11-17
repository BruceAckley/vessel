# Vessel

Tonal harmony tool

## Development

Install cmake and Reaper DAW.

Install dependencies:
`make cmake-configure`

Compile plugin build targets:
`make build`

### UI

TODO

### VS Code Debugging - audio processor

Launch Reaper
Debug -> Attach to Process
Search "Reaper"
Click the process
In Reaper, scan the folder `build/plugin/Vessel_artefacts/Debug/VST3` for VST3 plugins
Add the plugin to a track, A
Add a synth or piano to second track, B
Record arm track A
In track B's routing panel, set it to recieve midi from track A
In track A's routing panel, set it to send midi to track B
Breakpoints should now work
