Blender
-
### the basics
- watch part 1 to 4 of [this](https://youtu.be/B0J27sf9N1Y?list=PLjEaoINr3zgEPv5y--4MKpciLaoQYZB1Z) playlist, you can ignore the rest
- always update to latest LTS version
  - newer versions are faster and sometimes come with useful features, but they will require you to set those addons default values and maybe relearn some hotkeys
- steam's  blender allows to easily change the version  
![this](https://i.imgur.com/8fQO7zQ.png)  
- before updating to new version, check if all of your addons support that new version  
- you can set your default scene to be empty  
  - empty your scene  
    - in object mode  
    - `A` select all  
    - `X` delete  
  - set default scene  
    - `File`  
    - `Defaults`  
    - `Save Startup File`  

![this](https://i.imgur.com/DHxCm4G.png)  
- if it's too short, you can increase view distance TODO: this can probably be set by default  
  - `N` open right panel  
  - `View`  
  - increase `End`  

![this](https://i.imgur.com/AuQuXZu.png)
### addons

Blender has two addons to export meshes to source engine compatible formats
- [BlenderSourceTools](http://steamreview.org/BlenderSourceTools/)
  - old but simple
  - import and export
  - TODO: look into auto compilation

- [SourceOps](https://github.com/bonjorno7/SourceOps)
  - new with more features
  - only export
  - TODO: explain how to export and auto compile

#### how to add an addon
- Edit > Preferences > Add-ons  
![this](https://i.imgur.com/8VROy2T.png)  
- select the .zip file directly, you dont have to decompress it
- then check "Blender Source Tools", type it in the search bar if you can't find it  
![this](https://i.imgur.com/gNhk0sp.png)

#### Editing addons to set default values
TODO: explain how directly editing py files allows to set default values and avoid wasting time setting them every time

#### Importing
import smd or qc files (importing the qc will import everything written in that qc, collisionmodel, etc)  
![this](https://i.imgur.com/E6c4cwE.png)  
TODO: import options  

#### Editing
- TODO:
  - materials panel = vmts  
  - triangulate  
  - source engine's limits  
    - 64 material slots (see drawcalls)
    - vertex/triangle count, show bottom right
  - bones
    - weight painting
    - animations

#### Exporting
TODO: this

Source engine file formats
-
### VTF
- valve texture file, it's image data, like png or jpeg  
- use [VTFEdit](https://nemstools.github.io/pages/VTFLib-Download.html) to open .vtf files  
  - pendred will recommend you to use [VTFEdit-Reloaded](https://github.com/WereTech/VTFEdit-Reloaded), dont listen to him its garbage
- [more info](https://developer.valvesoftware.com/wiki/VTFEdit) on VTFEdit  
- it's not only for diffuse/albedo maps, it's used for other stuff, for example normal maps:  

![this](https://i.imgur.com/amT0PxM.png)
normal maps fake a higher level of detail by telling the game how shadows should be calculated on a flat surfaces, you get better performance than having more details with more polygons

#### Image compression formats
when you make a vtf file, you have to choose one of many image compression formats, some take more space but contain more accurate colors and support more things like alpha channels, others take less space but that's because the data is compressed (DXT formats), this is lossy compression meaning if you export your vtf back to png, the color won't be as "accurate" as the original png   

[list of all compression formats](https://developer.valvesoftware.com/wiki/VTF_(Valve_Texture_Format)#Image_data_format_table)  

what matters is the bpp (bit per pixel) amount, it's how many bits are used for each pixel  

the format `RGB888` for example has (for each pixel):  
- 8 bits for the red channel
- 8 bits for the green channel
- 8 bits for the blue channel  

for a total of 24 bits per pixel, this is why we say this format is 24 bpp  
there is 0 bits for the alpha channel, this format does not support an alpha channel (no transparency, the texture will be fully opaque)  

while `RGBA8888` has:
- 8 for red
- 8 for green
- 8 for blue
- 8 for alpha  

for a total of 32 bpp  
this means that a vtf in the `RGBA8888` format stores 8 more bits per pixel than the `RGB888` format, this results in a bigger file size, regardless if the alpha channel is actually used or not  

if you are not using any transparency in a vtf file with the `RGBA8888` compression format, your file is 33% bigger for no good reason  
#### which one you should use
it's gonna be `DXT1` or `DXT5` most of the time  
  
- `DXT1`
  - 4 bpp, that's 6x less than the uncompressed equivalent `RGB888`, meaning your texture's file size is 6x smaller
  - for textures that don't use an alpha channel  
    - this format does support alpha channel with the flag `1-bit alpha` but it's more complicated, it's one bit meaning the pixel is either opaque or fully transparent and nothing in between, no gradient alpha  

- `DXT5`
  - 8 bpp, this is 4x smaller than the uncompressed equivalent `RGBA8888`
  - for textures that do use an alpha channel  
  
[this](https://i.imgur.com/OR3xBsr.jpg) image shows visual differences between compressed (DXT) vtf vs non compressed

if you don't care and just use `DXT5` all the time instead of checking if it should be a `DXT1` instead, your textures will be twice the size  

this is how I reduced the total size of textures by 1gb  
![this](https://i.imgur.com/Fw1ZENV.png)

### VMT
- valve material, this is the file gmod uses to make materials
- it's just text, so you can open it with any text editor
  - color syntaxes for that file type exist and can be useful
- contains key value pairs,
  - key starts with $ character
  - value will often be a filepath to a .vtf file or number/vector
- [VMT-Editor](https://dima-369.github.io/VMT-Editor/) has easy to use interface to create/edit vmt files, also has cool feature like easily adding textures as png/jpeg/tga and it'll do the conversion to vtf for you
  - [more info](https://developer.valvesoftware.com/wiki/VMT_Editor) on VMT-Editor
- [more info](https://developer.valvesoftware.com/wiki/VMT) on .vmt files

picture below is an example of the content of a .vmt  
![this](https://i.imgur.com/ghmcjF9.png) 
- it doesnt matter if words are between quotations or not
  - except file paths that contains space characters, then yes you should have quotations for those
- the word on the first line is the shader, for models it needs to be `VertexLitGeneric`, in the picture above it's `LightmappedGeneric`, it means it's a material to apply to map brushes (walls, floors, etc)
- the parameter `$basetexture` is used to set the diffuse/albedo map (color data)
  - its value `bc\bc_bw01` is a filepath relative from `...\steamapps\common\GarrysMod\garrysmod\materials\`, meaning it points to the file `...\steamapps\common\GarrysMod\garrysmod\materials\bc\bc_bw01.vtf`
- all parameters dont necessarily point to a .vtf, `$surfaceprop` for example tells what sound should impacts make, what particle effect, etc
  - [list of all parameters](https://developer.valvesoftware.com/wiki/Category:Shader_parameters)
### QC
- like a vmt, but for models
- contains key value pairs
  - [list of all parameters](https://developer.valvesoftware.com/wiki/Category:QC_commands)
- open with any text editor
  - color syntax
- [more info](https://developer.valvesoftware.com/wiki/QC) on qc files  
  

example of qc file  
![this](https://i.imgur.com/Kfdxsmm.png)

### SMD
- this contains the mesh data, where are the polygons, what materials, bones, etc. it's like a .obj file  
- smd files can also contain animations  
- [more info](https://developer.valvesoftware.com/wiki/SMD) on smd files
  

example of smd file 
![this](https://i.imgur.com/aqvI6gK.png)  
- `M_MED_Sunrise_Palace_Body` is the name of the vmt material of that triangle (polygon)  
- the numbers below is position data of the triangle  
- you will never have to open this file in a text editor like that, just know that this is the data that it contains and gmod cannot read it, it needs to be compiled into a mdl file  

### MDL  
- this is the compiled model, the file that the game can read  
- [more info](https://developer.valvesoftware.com/wiki/MDL) on this format  
- it comes with other files  
  - `phy` collision model  
  - `vtx` mesh data  
  - `vvd` actual vertices data  

TODO: im probably forgetting something here

Dimensions
-
- 1 blender unit = 1 gmod unit
- your eye level (your pov) is 64 units high
- some people like to consider 1 gmod unit to be exactly 19.05mm, but know that some things like doors have bigger dimensions that would look crazy irl, but it's needed for gameplay/movement purposes
- [more info](https://developer.valvesoftware.com/wiki/Dimensions_(Half-Life_2_and_Counter-Strike:_Source)) on dimensions
  - when they talk about "hammer editor's grid", it's the same as our scale, so one unit on that grid is also one unit in gmod

Optimization
-
### in game fps vs file size
big file size results in lower fps because reading from disk lowers your fps, once it's loaded it's fine, todays gpus are more than enough to handle it  

this is why standing near (0, 0, 0) (in front of the blue lobster) can cause low fps, non networked entities end up at (0, 0, 0) and if you happen to be there, you will be reading from your disk all of those models  

and it's also why you see t posing models appear for a second in the air  

the amount of vertices doesnt affect fps much, it might increase file size a little bit, which makes reading the model slower which freezes/reduces fps when you load the model, but the high amount of vertices itself isn't hard to render

to reduce file size you:
- use compressed image formats (DXT)
- lower the resolution
- remove mipmaps  
  - this is pendreds idea, therefore its retarded, john green does not approve  
  

to directly improve fps in games you:

- reduce draw calls
- avoid high polygon count  
  - I said above that polygon count doesnt affect much fps, but if [this](https://youtu.be/hf27qsQPRLQ) applies to the source engine, there are probably some scenarios (watches, jewelry, etc with really high polygon counts) where polygons being smaller than the area of a 2x2 pixels square on your screen might affect performance, it could be a good idea to make a simpler [LOD](https://developer.valvesoftware.com/wiki/LOD_Models) for it  

### draw calls
every material in each model is a draw call  
let's say I have 10x the same model with `material A`  
it means I have 10 draw calls, for each model I ask the gpu to fetch `material A` (or something like that idk)  

instead I could have those 10 models combined into one model, that's one big model (file size increased, but not by much), the increased vertices amount is not a problem as seen above and now it's a single drawcall to get `material A`, believe it or not but this doubles your fps, they did it on csgo's nuke and saw a 40% fps improvement ([source](https://developer.valvesoftware.com/wiki/Static_Prop_Combine))  

this is scientifically proven btw, dont question it  
![this](https://i.imgur.com/OfYGjoy.png)  

Crowbar
-
- [official page (download)](https://steamcommunity.com/groups/CrowbarTool)
- [wiki](https://developer.valvesoftware.com/wiki/Crowbar)
- [github](https://github.com/ZeqMacaw/Crowbar)  
  
Go in the `Set Up Games` tab and set up gmod  
![this](https://i.imgur.com/PHgxCXd.png)

this is going to focus on compilation and decompilation only  

crowbar does the decompilation but to compile it actually uses `studiomdl.exe` which is located in `.../steamapps/common/GarrysMod/bin/`

### Decompilation
#### MDL Input  
![this](https://i.imgur.com/qIG3YQv.gif)  
- `File` select a single .mdl  
- `Folder` select all .mdl in a folder  
- `Folder and subfolders` recursively look in folders  
#### Output to
![this](https://i.imgur.com/jIvq7Mq.gif)  
- `Work folder` select your output folder  
- `Subfolder (of MDL input)` will create a folder (that you can name) where your .mdl file is and output there  
#### Options
TODO: elaborate on $definebone
#### and then press the `Decompile` button to decompile
### Compilation
#### QC Input  
![this](https://i.imgur.com/9V4ltnJ.gif)  
- `File` select a single .qc  
- `Folder` select all .qc in a folder  
- `Folder and subfolders` recursively look in folders  
#### Output to
![this](https://i.imgur.com/kG1ksKl.gif)  
- `Game's "models" folder` outputs to `.../steamapps/common/GarrysMod/garrysmod/models`  
- `Work folder` select your output folder  
- `Subfolder (of QC input)` will create a folder (that you can name) where your .qc file is and output there  
#### Options
![this](https://i.imgur.com/iPf4oRP.png)
- make sure you selected `Garry's Mod`
- add `-fastbuild`
  - will only create a `.dx90.vtx` and skip `.sw.vtx` (DX6/DX7), `.dx80.vtx`, and `.360.vtx`
- if you uncheck `Verbose` it might be faster but you won't get anything printed in the console

#### and then press the `Compile` button to compile

#### [more info](https://developer.valvesoftware.com/wiki/Compiling_a_model) about compilation

Other
-
- familiarize yourself with the software
- learn your keyboard shortcuts
- look for bottlenecks and see how to improve them
  - time expensive tasks, too repetitive, too long, etc
- automate stuff with scripts
  - python script for blender, etc
- be mindful and dont just do what youre used to on autopilot