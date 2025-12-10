# using MIDI keyboards on johngreen's piano

> [!NOTE]
> you can set this up while being on the server, no need to reconnect

### download the .dll

- [windows](https://github.com/FPtje/gmcl_midi/releases/tag/v0.2.0)
- [linux](https://github.com/FPtje/gmcl_midi/releases/tag/v0.2.1)
- [osx](https://github.com/FPtje/gmcl_midi/pull/7#issuecomment-658287602)

32bit one if you're on gmod 32 bit, 64bit one if you're on `x86-64`

### place the .dll

it has to be in your `.../steamapps/common/GarrysMod/garrysmod/lua/bin/`  
if the bin folder doesn't exist that's normal, create it

### do the command thing

make sure your midi keyboard is plugged in, use this website to make sure it works [https://hardwaretester.com/midi](https://hardwaretester.com/midi)  
run `loadmididll` in your console  

# the piano
the reason it doesn't sound shit is because the players are not only receiving what sounds to play, but also when exactly to play it  

# bug fixes
if no inputs are being detected, create  
`...\steamapps\common\GarrysMod\garrysmod\addons\testpiano\lua\autorun\client\piano_test_midi.lua`  
and put this in the .lua file
```lua
require("midi")

-- You MUST call this function before the MIDI hook will work. You need to connect to the actual MIDI device.
-- The default value for the "port" parameter is 0. An error will be thrown if there are no MIDI devices connected to the PC. Hence the check.
if table.Count(midi.GetPorts()) > 0 then -- use table.Count here, the first index is 0
    print("opening midi")
    midi.Open()
end

print(midi.Open())

hook.Add("MIDI", "print midi events", function(time, code, par1, par2, ...)
    -- The code is a byte (number between 0 and 254).
    print("A midi event happened at ".. time .. ", which is " .. SysTime() - time .. " seconds ago!")
    print("MIDI EVENT", code, par1, par2, ...)
    print("Event code:", midi.GetCommandCode(code))
    print("Event channel:", midi.GetCommandChannel(code))
    print("Event name:", midi.GetCommandName(code))

    -- The parameters of the code
    print("parameters", par1, par2, ...)

    if midi.GetCommandName(code) == "NOTE_ON" and par2 > 0 then
        -- key par1 has been pressed with par2 velocity (note: note has not yet been released)
    elseif midi.GetCommandName(code) == "NOTE_OFF" or midi.GetCommandName(code) == "NOTE_ON" and par2 == 0 then -- NOTE: some keyboards register the releasing of a key as a NOTE_ON with 0 velocity
        -- key par1 has been released.
    end
end)
```
it's basically just [this](https://github.com/FPtje/gmcl_midi/blob/master/examples/gmcl_midi.lua) without the part that makes it stop after 10 min  

then get in singleplayer, press some keys on your midi keyboard and check your console  

if there's something in your console, send it to me  
if there's nothing, you're cooked idk
