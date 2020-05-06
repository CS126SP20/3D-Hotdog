# 3D hotdog!

*Author: Angela Luo*

**Project Type**
Ingredients of a hotdog will be rendered on OpenGl using cinder. These ingredients will be interactive and users will be able
to spin and zoom in. They will also be able to add and remove certain ingredients as well as customize them. This is a very fun 
and simple program essentially for users to get used to 3D modelling. 

**Background Knowledge**
Only previous knowledge in this topic is how to create objects in blender and simple user interaction through cinder. 
I want to do this project because I love hotdogs and because I want to be experienced in working with 3D graphics and a Gui
system. In addition, I believe this project can be expanded and be used in fields of education like biology to render objects
that are not hotdogs.
 
**External Libraries / Tools**
- [OpenGL](https://libcinder.org/docs/guides/opengl/index.html): This will be used to render the hotdog and for the main logic of the project where users can interact with the hot dog.
- [Blender](https://www.blender.org/download/): This will be used to create a 3D hotdog object for me to render
- [ImGui](https://github.com/simongeilfus/Cinder-ImGui): This will be used to allow user customization

**TimeLine**
1. Week 1: Render and interact with a simple 3D square to make sure functions work correctly 
  - render square into Cinder
  - zoom in / out functions for the user
  - spin and allow users to interact with the object at 360 degrees
2. Week 2: Continue creating functions for 3D interactions and also create Blender hotdog ingredients. Integrate customizability
  - Improve upon user interactions of last week
  - Create ObjectInfo struct to store customization
  - use ImGui windows to let users change name, color, location, and type
3. Week 3: Add drop down
  - Create an item dropper that will handle the functionality of item dropping
  - Allow the dropper to turn off
  - only items caught by the hotdog stay

**Stretch Goals**
1. Allow users to draw on the hot dog
1. Make a 3D hamburger
---

