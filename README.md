# a list of things I (mrjohngreen) have done for diverge
###### these 2 INSANE masterpieces
- https://youtu.be/U45xWs0m4a8
- https://youtu.be/48eikj6NDHk  

![this](https://i.imgur.com/dR3I4Ok.png)
## luapack for linux 64 bit
###### status: untested and unused 😪
- binary module in c++
- [source code](https://github.com/therealjohngreen/luapacklinux64)
- complete and precise [instructions](https://i.imgur.com/xnohv0p.png) on how to do it
- useless since [this](https://github.com/A5R13L/gmsv_apakr_plugin) is a thing
## model optimization
###### status: done ✔
- python, bpy  
- 175k useless tris removed  

![file size](https://i.imgur.com/EDa4hMo.png)  

> before  
> ![before](https://i.imgur.com/Hjj22dM.png)  

> after  
> ![after](https://i.imgur.com/poEwJLe.png)  

![changelog](https://i.imgur.com/vo3zM1Y.png)
## texture optimization
###### status: done ✔
- [c++](https://github.com/therealjohngreen/VTFstuff) (using [VTFLib](https://github.com/NeilJed/VTFLib))
- batch convert image compression format to DXT1 (or DXT5 if non opaque alpha)  
it actually copy/pastes the vtf files you are looking for and then you have to use VTFEdit to batch convert them  
this is because I cant compress into DXT formats, I dont have nvDXTlib, a library needed to compress images into DXT format,  
its included in NVIDIA DDS Utilities 8.31 but the download link is gone, I can only get it from here https://archive.org/details/NVIDIA_DDS_Utilities_8.31 a sus .exe
- additional functions:
  - print directly image data
  - is the alpha of this image fully opaque (should this be in DXT1)
  - filter vtf files for specific compression format
  - count how many of each format
> reduced file size of textures by 1gb  
> ![source](https://i.imgur.com/Fw1ZENV.png)  

> wasnt done on map textures, most of them are already in DXT1 (todo: retake that screenshot but align the stuff so its more readable)  
> ![this](https://i.imgur.com/hJKX70c.png)  

![changelog](https://i.imgur.com/Ga1HCX8.png)
## duplicate textures
###### status: unknown ❓
> used [this](https://github.com/qarmin/czkawka) on all textures  
> ![this](https://i.imgur.com/tT0pjOP.png)  

update: hl2 and css content was removed, this should also fix some of the particles  

## dupe combine
###### status: done ✔
- nodejs, python, bpy
- less drawcalls, doubles fps, [sauce](https://www.mapcore.org/articles/tutorials/static-prop-combine-in-csgo-r111/)
- 150 vs 1 entity
- windows only (no linux studiomdl)
- auto creates needed vmts
- [discord bot slash command](https://i.imgur.com/knj1g3Q.png), send the dupe .json and it sends back the 7zipped model
- can do multiple dupes at the same time
- can directly read dupe .txt files ([lmza decompress](https://github.com/WilliamVenner/gmod-lzma-rs) and parses the data)

## discord bot
###### status: done ✔
- discordjs, full rewrite
- very documented but useless since we're just copy pasting ai slop now
- mysql2
  - 2x faster [source](https://i.imgur.com/bCwqrwo.png)
  - ez to use (u can await a query)
- [atomic operations for auctions](https://i.imgur.com/bGZ8mPg.png)
- ticket system  

![this](https://i.imgur.com/IaZdvyT.png)
## billiard
###### status: either very close to finished, or not at all
- lua
- low tickrate makes the balls vibrate and keep moving, there has to be a better way to physically simulate them
- replace usmg
> fixed textures  
> ![this](https://i.imgur.com/AZ2snCD.png)  

## holylib for linux 64 bit
###### status: doesnt work
- binary module in c++
- fixes
  - someone [doesnt want to use the stl max](https://github.com/danielga/sourcesdk-minimal/blame/0b3281f3bdd4048c35c45a179a5c414c1ef4dfb0/public/studio.h#L1776) but [forgot to correctly type their max function](https://github.com/danielga/sourcesdk-minimal/blob/0b3281f3bdd4048c35c45a179a5c414c1ef4dfb0/public/tier0/basetypes.h#L185-L191) 
  - a week ago he changed these functions so [they return 64 bit unsigned int](https://github.com/RaphaelIT7/gmod-holylib/blame/8b4b56fa5e899fc161ee12bfc7bfe370f06beefd/source/sourcesdk/filesystem_things.h#L483-L486), he says its because "gmod's filesystem changed", but these functions [havent changed in 9 years](https://wiki.facepunch.com/gmod/Update_Preview_Changelog#:~:text=Applied%20potential%20filesystem%20optimization%20suggested%20by%20the%20community), maybe hes refering to [this](https://wiki.facepunch.com/gmod/Update_Preview_Changelog#:~:text=Applied%20potential%20filesystem%20optimization%20suggested%20by%20the%20community), so I edited it to return 32bit like gmod does, but this might break when this new update comes out
  - [this](https://i.imgur.com/J3XRkBM.png)...  
  - commented [this](https://github.com/RaphaelIT7/gmod-holylib/commit/4e2be8c64fb4fecb0f541e8da741002549c1a090#diff-38f68bc3a4c9a69e07f9aaf76b0e0f9e77360c9d75097af3e8642379878decc3R230) out
- [source code](https://github.com/RaphaelIT7/gmod-holylib)
## simfphys optimization
###### status: broke ❌
- lua
- stopped networking of `gmod_sent_vehicle_fphysics_base` when it's outside of your pvs, this is mostly a clientside fps optimization because the player stops rendering the car model
- how to optimize networking? stop the networking of `gmod_sent_vehicle_fphysics_wheel` when outside of the pvs, the TRANSMIT_ALWAYS state is forced by either:
  - the rope/elastic constraints, [simfphys](https://github.com/CosmicStar98/simfphys-backup/blob/9903f5f4fb39633ec0666155fc575aa73c6d4939/simfphys_base/lua/entities/gmod_sent_vehicle_fphysics_base/spawn.lua#L689-L712), [source engine](https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/game/server/rope.cpp#L129-L150)
  - the particles, [simfphys](https://github.com/CosmicStar98/simfphys-backup/blob/9903f5f4fb39633ec0666155fc575aa73c6d4939/simfphys_base/lua/entities/gmod_sent_vehicle_fphysics_wheel.lua#L48-L72), [source engine](https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/game/server/particle_system.cpp#L185-L191)  
  ###### note that the transmit state of an entity needs to be the same as their parent/children
- [archive](https://i.imgur.com/coTPDUv.png)
###### update: [it broke](https://i.imgur.com/anGPO1m.jpg)
- the reason probably has to do with [this](https://i.imgur.com/h5nkogw.png)
- this problem never happens on my end  

https://github.com/user-attachments/assets/b2e1c439-b9fc-4f42-b8ac-c852fa09423d

## shift click item transfer
###### status: done ✔
- lua
- dragging the item is annoying, now you can shift click to transfer the item like in minecraft
- it kinda simulates prediction so that even people with high ping can send a bunch of items in quick succession  
- works with any item size  
- ctrl click to move multiple items coming soon maybe  

https://github.com/user-attachments/assets/860071d7-e989-4ee8-a157-dfc1c462c6bd

## sounds going through walls
###### status: done ✔
- lua
- you could hear people through walls in some places
- the lua script draws a line in front of you that indicates if sound can pass through
- also shows content/surface flags of what it touches
- shows XY coordinates in the middle of the screen so that we know where is every screenshot from
- turns out some [doorframes](https://i.imgur.com/MAoK6Z2.png) were not physically solid
- and map geometry is the only thing that blocks sound (unless it has the translucent flag)  

![this](https://i.imgur.com/6SETiqb.png)  

## john green coin
- nodejs, sqlite
- stock exchange on a discord bot, only tradable thing was the john green coin  

![this](https://i.imgur.com/gux3oMF.png)  

## blackjack part 1 - finding cheaters
###### status: done ✔
- lua
- some people have an advantage at the blackjack tables, they managed to completely empty some tables
- this script can observe blackjack games from far away, as long as the table is in your pvs
- net messages are overridden to ignore distance checks (yes they are clientside) and keep the hands value on the screen even after the game is done, so I have the time to look at them
- it shows the countdown before the game starts
- it counts win/loss/tie
- it shows who's in the casino  

![this](https://i.imgur.com/iMafsLy.png)  

## blackjack part 2 - there was no cheaters, just a garbage blackjack gmod addon
###### status: done ✔
- lua
- no more infinite split
- unnatural blackjack no longer gives 3:2 payout
- no more split double double  

![this](https://i.imgur.com/cSXaMFT.png)  

> note the date  
> ![this](https://i.imgur.com/JQSmLX6.png)  

## blackjack part 3 - actually i was the cheater
###### status: done ✔
- lua
- c++ (rewrote the gmod prng [here](https://github.com/therealjohngreen/gmodprngc-) and [here](https://github.com/therealjohngreen/gmodprngforsbox/blob/master/GmodRandom.cs) in c# for s&box)
- a "Think" hook in another addon would call `math.randomseed(os.time())`
- [this](https://github.com/spawnmason/randar-explanation/blob/master/README.md) was the inspiration, i was lucky that the code was shit otherwise i wouldve never found something like this  

[<img src="https://img.youtube.com/vi/mkRwIpTHsCY/hqdefault.jpg" width="854" height="480"/>](https://www.youtube.com/embed/mkRwIpTHsCY)  

## blackjack part 4 - but then why are people still emptying tables?
https://www.youtube.com/watch?v=56iFMY8QW2k  
![this](https://i.imgur.com/Sx5P69b.png)  

yes, those who own blackjack tables dont put enough money/have very high bet limits and allow this to happen

## items drop through the floor
###### status: done ✔
- lua
- the function `getItemDropPos()` is used to determine where the dropped item should appear
- when looking at a certain angle, that drop position will be exactly at the floor's height, meaning the dropped item will be halfway into the floor
- displacements with a power of 4 also didnt help

https://github.com/user-attachments/assets/e20efc74-a23a-4867-8f9e-2d02c0c9d31a

## server logs database
###### status: done ✔
- mysql
- the table had no index, meaning the staff team would actually wait 30-40s for a full table scan on 18-20 million rows every time they wanted to search logs
- added a composite index on "steamID" and "category", query time always under 1s
- added a fulltext index to quickly search any word in log messages, query time always under 3s  

this is a duct tape solution, a better idea is to index the date since the date column has the highest cardinality and staff members never really search for something older than an hour  
> execution time (in seconds) as a function of number of rows  
> the number of rows here represents the range of time we are searching in hours  
> if 1 week = 168h, then getting all logs in a 1 week period takes ~5.8s
> ![this](https://i.imgur.com/5d93mlU.png)  
> searching logs in the past 10 hours would take under 1 second  
> this means we wouldnt need to use any other index and we could use `LIKE '%...%'`  
> which is better than the fulltext because fulltext search requires us to type the exact word  

there are many other problems
- nothing is fucking normalized, that server logs table is 5gb but can in theory be 3x smaller  
- a spatial index would be useful to search logs by location (we are never getting this)  
- the date is **not** in UTC, its in whatever the timezone of the machine is, so GMT or BST, meaning even if staff members have the ability to search by date, it's so complicated no one bothers, this is why indexing the date column is not an option  

## subtick piano
###### status: done ✔ (not on the server yet)
- lua
- with a tickrate of 16 (that goes down to 8) and the lag, the piano will sound like shit to other players
- the solution is something similar to the subtick system in cs2, but it's the other players who are replaying the sounds at the right time (with a 1s delay)
- made from scratch so i kept it simple, meaning this doesnt have the "teleport bug", annoying interface, sitting animation, etc.
- doesnt broadcast net messages to everyone

## small bug fixes
> chat color bug  
> ![this](https://i.imgur.com/BPihnKD.png)  
> it modifies a reference of the color instead of a copy  
> ![this](https://i.imgur.com/4yD5ygm.png)  

> flying blackjack tables  
> ![this](https://i.imgur.com/J0ldIJq.png)  
> i guess DropToFloor() doesnt work anymore or something  
> ![this](https://i.imgur.com/uwARjxW.png)


## there wont be anything new for a while
![this](https://i.imgur.com/XJ6lDJi.png)  

## below is a list of knowledge with which I have endowed Pendred
- blender
  - [directly modifying default parameters of blender addons](https://i.imgur.com/Bo5utyJ.png)
- hammer
  - [texture alt right click](https://i.imgur.com/S7bClgv.gif)
  - [corners...](https://i.imgur.com/Pd2fDz1.png)
  - [center helpers](https://i.imgur.com/RLSzk8W.png)
  - [notjunc](https://i.imgur.com/T6RMHqW.png)
- rdbms
  - [composite indexes](https://i.imgur.com/7x2Qcmz.png)
  - [fulltext](https://i.imgur.com/gK0NYMi.png)
  - [just the fucking idea of an index](https://i.imgur.com/NMM79i7.png)
  - [testing queries on tiny tables is fucking useless](https://i.imgur.com/YX3JQSu.png)
- other
  - [big O notation](https://i.imgur.com/uc2tivz.png)
  - [high school math](https://i.imgur.com/mUF8Zu5.png)
