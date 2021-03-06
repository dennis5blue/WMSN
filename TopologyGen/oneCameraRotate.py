# To execute in the blender console
# filename = "/home/dennisyu/Documents/WMSN/TopologyGen/oneCameraRotate.py"
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
cameraPos = (-0.7, 1.3, 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*10.0/180)), 1.3-0.3*math.sin(math.pi*10.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*80.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*20.0/180)), 1.3-0.3*math.sin(math.pi*20.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*70.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*30.0/180)), 1.3-0.3*math.sin(math.pi*30.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*60.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*40.0/180)), 1.3-0.3*math.sin(math.pi*40.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*50.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*50.0/180)), 1.3-0.3*math.sin(math.pi*50.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*40.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*60.0/180)), 1.3-0.3*math.sin(math.pi*60.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*30.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*70.0/180)), 1.3-0.3*math.sin(math.pi*70.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*20.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*80.0/180)), 1.3-0.3*math.sin(math.pi*80.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*10.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.7+(0.3-0.3*math.cos(math.pi*90.0/180)), 1.3-0.3*math.sin(math.pi*90.0/180), 0.1)
cameraRotation = (math.pi*76.0/180, math.pi*0.0/180, -math.pi*0.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);


bpy.data.scenes["Scene"].render.resolution_x = 1280*2;
bpy.data.scenes["Scene"].render.resolution_y = 720*2;
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
logFileName="//home/dennisyu/Documents/WMSN/TestSequences/test_paperRotate_png/log.txt"
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
        bpy.data.images[RR].save_render("/home/dennisyu/Documents/WMSN/TestSequences/test_paperRotate_png/camera_"+str(c)+".png");
        c = c + 1; 

logFile.close()
