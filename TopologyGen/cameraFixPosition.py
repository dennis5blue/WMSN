# To execute in the blender console
# filename = "/home/dennisyu/Documents/WMSN/TopologyGen/cameraFixPosition.py"
# exec(compile(open(filename).read(), filename, 'exec'))

import bpy
import random
import math

# way of remove object, we need to select the objects first
# gather list of items of interest.
#candidate_list = [item.name for item in bpy.data.objects if item.type == "CAMERA"]
#print(candidate_list)

# select them only.
#bpy.data.objects["Lamp"].select = False
#bpy.data.lamps["Lamp"].type = "SUN"
#bpy.data.lamps["Lamp"].sky.use_sky = True

#for object_name in candidate_list:
#  bpy.data.objects[object_name].select = True


# remove all objects except the city.
bpy.ops.object.select_all(action="SELECT")
bpy.data.objects["SCG_city"].select = False
bpy.data.objects["SCG_terrain"].select = False
bpy.data.objects["SCG_water"].select = False
bpy.ops.object.delete()

bpy.data.objects["SCG_city"].location    = [ -2.8,-3.2,-3.0]
bpy.data.objects["SCG_terrain"].location = [ -2.8,-3.2,-3.0]
bpy.data.objects["SCG_water"].location   = [ -2.8,-3.2,-3.0]
#bpy.data.objects["Lamp"].location        = [ -2.0,2.0, 3.0]




# add light
scene = bpy.context.scene
lamp_data = bpy.data.lamps.new(name="sun1", type='SUN')
lamp_data.energy = 1.0
lamp_data.sky.use_sky = True
lamp_data.sky.use_atmosphere = True
lamp_data = bpy.data.lamps.new(name="sun2", type='HEMI')
lamp_object = bpy.data.objects.new(name="sun1", object_data=lamp_data)
scene.objects.link(lamp_object)
lamp_object.location = (-1.0, 1.0, 1.5)
lamp_object.select = True

lamp_data = bpy.data.lamps.new(name="sun2", type='SUN')
lamp_data.energy = 1.0
lamp_data.sky.use_sky = True
lamp_data.sky.use_atmosphere = True
lamp_data = bpy.data.lamps.new(name="sun2", type='HEMI')
lamp_object = bpy.data.objects.new(name="sun2", object_data=lamp_data)
scene.objects.link(lamp_object)
lamp_object.location = (-0.5, 0.5, 1.5)
lamp_object.select = True

scene.objects.active = lamp_object

#cameraNumPerCluster = 6
#clusterNum = 1 
#cameraNum  = cameraNumPerCluster*clusterNum;

#add camera (fix position)
#Camera cluster 1
cameraPos = (-0.36, 0.5, 0.1)
cameraRotation = (1.5, 0.0, 500.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.36, 0.5, 0.11)
cameraRotation = (1.5, 0.0, 500.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.33, 0.5, 0.1)
cameraRotation = (1.5, 0.0, 500.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.36, 0.5, 0.1)
cameraRotation = (1.5, 0.0, 600.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.36, 0.5, 0.11)
cameraRotation = (1.5, 0.0, 600.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.33, 0.5, 0.1)
cameraRotation = (1.5, 0.0, 600.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Camera cluster 2
cameraPos = (0.22, 1.2, 0.1)
cameraRotation = (1.3, 0.0, 3.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.22, 1.2, 0.11)
cameraRotation = (1.3, 0.0, 3.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.25, 1.2, 0.11)
cameraRotation = (1.3, 0.0, 3.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.22, 1.2, 0.1)
cameraRotation = (1.3, 0.0, 3.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.22, 1.2, 0.11)
cameraRotation = (1.3, 0.0, 3.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.25, 1.2, 0.11)
cameraRotation = (1.3, 0.0, 3.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Camera cluster 3
cameraPos = (-0.5, 0.1, 0.07)
cameraRotation = (1.3, 0.0, 6.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, 0.1, 0.06)
cameraRotation = (1.3, 0.0, 6.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.53, 0.1, 0.07)
cameraRotation = (1.3, 0.0, 6.0)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, 0.1, 0.07)
cameraRotation = (1.3, 0.0, 5.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, 0.1, 0.06)
cameraRotation = (1.3, 0.0, 5.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.53, 0.1, 0.07)
cameraRotation = (1.3, 0.0, 5.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Camera cluster 4
cameraPos = (-0.5, -0.1, 0.07)
cameraRotation = (1.3, 0.0, 4.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, -0.1, 0.06)
cameraRotation = (1.3, 0.0, 4.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.53, -0.1, 0.07)
cameraRotation = (1.3, 0.0, 4.5)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, -0.1, 0.07)
cameraRotation = (1.3, 0.0, 3.95)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, -0.1, 0.06)
cameraRotation = (1.3, 0.0, 3.95)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.53, -0.1, 0.07)
cameraRotation = (1.3, 0.0, 3.95)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Camera cluster 5
#Note that cameras in this cluster does not install at the same crossroad
cameraPos = (-0.5, 0.5, 0.07)
cameraRotation = (math.pi*74.485/180, 0.0, math.pi*257.83/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.58, 0.53, 0.08)
cameraRotation = (math.pi*66.0/180, 0.0, math.pi*150.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.1, 1.0, 0.07)
cameraRotation = (math.pi*73.296/180, 0.0, math.pi*256.83/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.55, 0.0, 0.07)
cameraRotation = (math.pi*89.025/180, 0.0, math.pi*235.83/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.18, 0.72, 0.07)
cameraRotation = (math.pi*68.755/180, 0.0, math.pi*257.83/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.28, 0.2, 0.07)
cameraRotation = (math.pi*79.214/180, 0.0, math.pi*181.83/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);


bpy.data.scenes["Scene"].render.resolution_x = 480*2;
bpy.data.scenes["Scene"].render.resolution_y = 360*2;
# object has a attribute named type which can query the type
# print(str(object.type))
for object in bpy.data.objects:
    print(object.name+" is at location " + str(object.location))

# to setup the camera field of view(FoV)
#bpy.data.scenes["Scene"].camera.data.angle_x
#bpy.data.scenes["Scene"].camera.data.angle_y
	
	
print('\nPrint Scenes...'); 
sceneKey = bpy.data.scenes.keys()[0]; 
print('Using Scene['  + sceneKey + ']');
c=0;
logFileName="//home/dennisyu/Documents/WMSN/TestSequences/test_paper360_30cam_png/log.txt"
logFile=open(logFileName,"w+")
for obj in bpy.data.objects: 
# Find cameras that match cameraNames 
    if ( obj.type =='CAMERA'): 
        print("Rendering scene["+sceneKey+"] with Camera["+obj.name+"]")
        logFile.write("Rendering scene["+sceneKey+"] with Camera["+obj.name+"]\n") 
        location = obj.location
        rotation = obj.rotation_euler 
        logFile.write("Pos "+str(location.x)+" "+str(location.y)+" "+str(location.z)+" Dir "+str(rotation.x)+" "+str(rotation.y)+" "+str(rotation.z)+"\n")
        # Set Scenes camera and output filename 
        bpy.data.scenes[sceneKey].camera = obj 

        # Render Scene and store the scene 
        bpy.ops.render.render( write_still=True ); 
        RR = "Render Result";
        bpy.data.images[RR].save_render("/home/dennisyu/Documents/WMSN/TestSequences/test_paper360_30cam_png/camera_"+str(c)+".png");
        c = c + 1; 

logFile.close()
