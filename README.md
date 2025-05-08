This project, co-authored by classmate Pierre Sintre, aims at comparing three different numerical integration methods to simulate 
the motion of a spinning top. It also includes a graphics part, where, using OpenGL, you can view the simulation as it happens and
interact with it. The integration models are the [Euler-Cromer integrator](https://en.wikipedia.org/wiki/Semi-implicit_Euler_method),
[Newark](https://en.wikipedia.org/wiki/Newmark-beta_method) and [Runge-Kutta](https://fr.wikipedia.org/wiki/M%C3%A9thodes_de_Runge-Kutta)

To run the simulations, open the project in Qt creator using the file sortie_graphique/simulation_complete/simulation_complete.pro .
This is where the rest of the project takes place: simple cones and a general top will be integrated 
(see explanation of graphical simulation below), and you will have access to all the text output test files.

 - Graphical output: click on the icon at the bottom right of your screen, above the green arrow, 
and selecting Qt_GL under ‘Run’, you simply press the green arrow to launch the 
simulation. Here again, an error may appear: ‘No rule to make target “../general/libgeneral.a”, needed by “ex_05_text.exe”.’ 
appears: in this case, you need to perform the same operation: go to ‘sortie_graphique/build-simulation_complete-Desktop_Qt_5_14_1_MinGW_32_bit-[Debug or Profile or Release]/general’ 
and delete the libgeneral.a file.

When the simulation is launched, you will see 4 spinning tops on the screen: the one to your left will be 
a simple cone integrated by an Euler-Cromer integrator; the one in the centre is a simple cone integrated by a Newmark integrator and the one on your right is also a simple cone, integrated by a Runge-Kutler integrator. 
integrator and the one on your right is also a simple cone, integrated by a Runge-Kutta integrator, 
Finally, the spinning top in the background is a general-purpose spinning top integrated by an Euler-Cromer integrator.
This simulation therefore condenses exercise P11 (plotting the centre of mass for the three spinning tops), P12 (general spinning top) and P13 (integrator of the centre of mass for the three spinning tops). 
P13 (Newmark and Runge-Kutta integrator). 
The initial parameters of the 4 spinning tops are: (0 0.4 0) and (0 0 70), density 0.1, radius 0.9, height 2.
The additional viewpoint modification commands we have implemented are as follows:
-C and V offer a view of the central spinner, from above and from the side respectively.
-Z and X offer a view of the left router, from above and from the side respectively.
B and N show a view of the right-hand spinner, from above and from the side respectively.
-G and H show a view of the spinner from the rear, from above and from the side respectively.
NOTE: We have chosen to integrate the general spindle moulder with the Euleur-Cromer integrator, because it is with this integrator 
that we obtain the best results. As you can see, the movement is very similar to that of the 
simple cone with the same integrator.

 - Text output: by changing ‘Qt_GL’ to ‘text’ in the same icon above the green run arrow, 
you will have access to the text output of our project. The default program is called ‘invariants_mouvements.cc’ 
and corresponds to a brief simulation of a simple cone, where we display the evolution of its invariants of 
invariants and its P and P point values.
You can then run all the other text output programs by simply changing line 11 of the 
text.pro, below ‘SOURCE += \’: the programs present are “testVecteur.cc”, “testMatrice.cc”, 
“testToupie.cc”, “testIntegrateur[123].cc”, “exerciceP9.cc” and “invariants_mouvement.cc”.




