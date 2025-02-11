# a list of things I (mrjohngreen) have done for diverge
###### these 2 INSANE masterpieces
- https://youtu.be/U45xWs0m4a8
- https://youtu.be/48eikj6NDHk  

![this](https://i.imgur.com/dR3I4Ok.png)
## luapack for linux 64 bit
###### status: untested and unused 😪
- binary module in c++
- [source code](https://github.com/therealjohngreen/luapacklinux64)
- complete and precise [instructions](https://discord.com/channels/619968869125062656/771506522970783795/1282549825887277118) on how to do it, [archive](https://i.imgur.com/xnohv0p.png)
- useless since [this](https://github.com/A5R13L/gmsv_apakr_plugin) is a thing
## model optimization
###### status: done ✔
- python, bpy
- code not released
- [result](https://discord.com/channels/619968869125062656/771506522970783795/1255902657801879552)  
![file size](https://i.imgur.com/EDa4hMo.png)
- 175k useless tris removed
- before  
![before](https://i.imgur.com/Hjj22dM.png)
- after  
![after](https://i.imgur.com/poEwJLe.png)
- [changelog](https://discord.com/channels/619968869125062656/771506516762820688/1269676598735540276), [archive](https://i.imgur.com/vo3zM1Y.png)
## texture optimization
###### status: done ✔
- c++, VTFLib
- [source code](https://github.com/therealjohngreen/VTFstuff)
- batch convert image compression format to DXT1 (or DXT5 if non opaque alpha)  
it actually copy/pastes the vtf files you are looking for and then you have to use VTFEdit to batch convert them  
this is because I cant compress into DXT formats, I dont have nvDXTlib, a library needed to compress images into DXT format,  
its included in NVIDIA DDS Utilities 8.31 but the download link is gone, I can only get it from here https://archive.org/details/NVIDIA_DDS_Utilities_8.31 a sus .exe
- additional functions:
  - print directly image data
  - is the alpha of this image fully opaque (should this be in DXT1)
  - filter vtf files for specific compression format
  - count how many of each format
- reduced file size of textures by 1.1gb [source](https://i.imgur.com/Fw1ZENV.png)
- wasnt done on map textures, most of them are already in DXT1 (todo: retake that screenshot but align the stuff so its more readable)  
![this](https://i.imgur.com/hJKX70c.png)  
- [changelog](https://discord.com/channels/619968869125062656/771506516762820688/1292577481303392318), [archive](https://i.imgur.com/Ga1HCX8.png)
## duplicate textures
###### status: unknown ❓
- used this on all textures <https://github.com/qarmin/czkawka>
![this](https://i.imgur.com/tT0pjOP.png)
## dupe combine
###### status: done ✔
- python, bpy
- code not released
- less drawcalls, doubles fps, [sauce](https://www.mapcore.org/articles/tutorials/static-prop-combine-in-csgo-r111/)
- 150 vs 1 entity
- windows only (no linux studiomdl)
- auto creates needed vmts
- [discord bot slash command](https://i.imgur.com/knj1g3Q.png), send the dupe .json and it sends back the 7zipped model
- not done:
  - nocollided props (ez)
  - support the dupe as a .txt instead of .json (80% done in js)
## discord bot
###### status: 95% done, database untested, wrong channel ids
- discordjs, full rewrite
- [source code](https://github.com/Pendred/divergebot-new)
- very VERY documented
- mysql2
  - 2x faster [source](https://i.imgur.com/bCwqrwo.png)
  - ez to use (u can await a query)
- atomic operations for auctions
## billiard
###### status: either very close to finished, or not at all
- fixed textures  
![this](https://i.imgur.com/AZ2snCD.png)
- things to do
  - Ive rewritten the addon, networking is optimized and now you have a power gauge instead of physically pushing the ball with the cue, but the physics between the balls and the table behave differently in my addon, I'll try to directly add this into the original addon and test it there
  - replace usmg
## holylib for linux 64 bit
###### status: doesnt work
- binary module in c++
- fixes
  - someone [doesnt want to use the stl max](https://github.com/danielga/sourcesdk-minimal/blame/0b3281f3bdd4048c35c45a179a5c414c1ef4dfb0/public/studio.h#L1776) but [forgot to correctly type their max function](https://github.com/danielga/sourcesdk-minimal/blob/0b3281f3bdd4048c35c45a179a5c414c1ef4dfb0/public/tier0/basetypes.h#L185-L191) 
  - a week ago he changed these functions so [they return 64 bit unsigned int](https://github.com/RaphaelIT7/gmod-holylib/blame/8b4b56fa5e899fc161ee12bfc7bfe370f06beefd/source/sourcesdk/filesystem_things.h#L483-L486), he says its because "gmod's filesystem changed", but these functions [havent changed in 9 years](https://wiki.facepunch.com/gmod/Update_Preview_Changelog#:~:text=Applied%20potential%20filesystem%20optimization%20suggested%20by%20the%20community), maybe hes refering to [this](https://wiki.facepunch.com/gmod/Update_Preview_Changelog#:~:text=Applied%20potential%20filesystem%20optimization%20suggested%20by%20the%20community), so I edited it to return 32bit like gmod does, but this might break when this new update comes out
  - this...  
  ![this](https://i.imgur.com/J3XRkBM.png)
  - commented [this](https://github.com/RaphaelIT7/gmod-holylib/commit/4e2be8c64fb4fecb0f541e8da741002549c1a090#diff-38f68bc3a4c9a69e07f9aaf76b0e0f9e77360c9d75097af3e8642379878decc3R230) out



- [source code](https://github.com/RaphaelIT7/gmod-holylib)

## simfphys optimization
###### status: done ✔
- stopped networking of `gmod_sent_vehicle_fphysics_base` when it's outside of your pvs, this is mostly a clientside fps optimization because the player stops rendering the car model
- how to optimize networking? stop the networking of `gmod_sent_vehicle_fphysics_wheel` when outside of the pvs, the TRANSMIT_ALWAYS state is forced by either:
  - the rope/elastic constraints, [simfphys](https://github.com/CosmicStar98/simfphys-backup/blob/9903f5f4fb39633ec0666155fc575aa73c6d4939/simfphys_base/lua/entities/gmod_sent_vehicle_fphysics_base/spawn.lua#L689-L712) 
  - the particles, [simfphys](https://github.com/CosmicStar98/simfphys-backup/blob/9903f5f4fb39633ec0666155fc575aa73c6d4939/simfphys_base/lua/entities/gmod_sent_vehicle_fphysics_wheel.lua#L48-L72), [source engine](https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/game/server/particle_system.cpp#L185-L191)  
  ###### note that the transmit state of an entity needs to be the same as their parent/children