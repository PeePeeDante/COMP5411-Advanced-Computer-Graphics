# Quick Demo of Mesh Viewer Assignment

## Assignment 0: Preparation
Original Mesh </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Lion.png"  width="400"> </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Lion%20Mesh.png"  width="400"> </br>

Compute normal for each vertex </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Lion%20Mesh%20Normal.png"  width="400"> </br>

## Assignment 1: Smoothing
### Results
Original Bunny </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Original%20B.png"  width="400"> </br>
Smoothed Bunny </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Smoothed%20B1.png"  width="400"> 
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Smoothed%20B2.png"  width="400"> </br>
Original Feline </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Original%20F.png"  width="400"> </br>
Smoothed Feline </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Smoothed%20F1.png"  width="400"> 
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Smoothed%20F2.png"  width="400"> </br>
Original 3 Holes </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Original%203H.png"  width="400"> </br>
Smoothed 3 Holes </br>
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Smoothed%203H1.png"  width="400"> 
<img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/Smoothed%203H2.png"  width="400"> </br>


## Assignment 2: Naive Laplacian Deformation 
### Introduction
Mesh deformation is the practice of manipulating shapes of objects via deformation of the given surface of objects. Common examples include, but not restricted to, deformation of elastic balls when bounced, or simple movement of characters’ limbs, etc. While there may exist a direct approach that changes the displacements vertex-by-vertex, the computation overhead is too expensive for immediate and continuous animated response. Another approach is to create in-between shape linear interpolation for deformations. However, in many cases, deformations and distances are non-linear, e.g. curved planes, leading to unnatural deformation results. This project aims to implement the Laplacian-based surface editing algorithm, proposed by O. Sorkine et. al., which utilizes the intrinsic surface representation that preserves local surface details during surface editing. The methodology section explains the algorithm and its mathematical theory behind. In the result section, we will show the screenshots of the implementation results of some deformed mesh shapes. Lastly, we will discuss some of the limitations of this algorithm in the discussion section.
### Methodology (see assignment2.pdf)
### Results
The following are some results of the mesh deformation using the Laplacian-based surface editing algorithm that is proposed by O. Sorkine et. al. We will show the screenshotted deformation results of the three object meshes, namely, “bunny.obj”, “face.obj” and “dinosaur.obj”. The purple regions are the user-specified fixed points, which are used as deformation handles in the application. <\br>

| Original | After Deformation |
| --- | --- |
| <img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/ass2%20bunny.png"  width="400"> | <img src="https://github.com/PeePeeDante/COMP5411-Advanced-Computer-Graphics/blob/main/assignment/images/ass2%20deformed%20bunny.png"  width="400"> |



