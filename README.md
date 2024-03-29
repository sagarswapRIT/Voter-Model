# Voter-Model
My capstone project for MS in Data Science at RIT which has now been turned into a research project under Dr. Nishant Malik. The project was intially about simulating voter behaviour in a co-evolving network model. However the scope of the project has been expanded and is now focused on Game Theory. In this project we study the phenomenon of altruism in the Prisoner's Dilemma Scenario. Here, nodes can either co-operate or defect based on their previous experience, switching strategies as needed. The reference paper for this model is https://academic.oup.com/comnet/article/6/1/1/3935082 .

The model utilizes real world datasets from https://snap.stanford.edu/data/ which contain large scale datasets, managed by Standford University.

![image](https://github.com/sagarswapRIT/Voter-Model/assets/24601204/5edd6bcd-10f8-45b6-a547-85fd56a4816d)


To compile pgm:
g++ VoterModelPrototype.cpp -o outputName

To run pgm:
./output

If you want to see stats of just 1 simulation, run Pop_vs_DiscEdge.py

If you want to see stats of a group of simulations, first place them all in 1 folder inside the output folder
Then run GenerateMultiPlotData.py, be sure to specifyoutputfile along with the input folder
Then run SpaghettiPlot.py and BoxPlots.py