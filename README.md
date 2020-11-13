# 移动机器人未知环境探险
C , BFS , Dijkstra .
这个项目是本人的高级语言（C语言）程序设计这门课程的实验项目，项目要求的所有功能（在下面的项目描述中）基本都已实现，上传一下供大家交流学习（编译环境为Visual Studio Code(MinGW-w64编译器)）。

项目描述：
考虑一个简单的移动机器人，它能够在平面上沿着可以行走的路径移动，并能够记录自身的运行轨迹。假定在每一个地点，机器人移动的方向只能是前、后、左、右、右前、右后、左前和左后八个方向，而且也只能感知到其周围局部八个位置的信息(是可行路径、不可达区域还是目标点)。编写程序，由文件读取一张100x100 个格点的平面地图(’.‘表示不可行走的地域，’+‘表示机器人可行走的路径，’*‘表示机器人要寻找的探险目标点，’#'表示特殊重要的、必须到达的目标点)，让移动机器人按照感知和移动规则在该地图所表示的区域内探险。
要求：1) 机器人能找到所有的目标点和路径然后返航；2) 根据探险的经历绘制出该区域的目标-路线图(注意，不能直接把所给出的地图画出来就行了，因为机器人的目标是探险，它事先并不知道全局的目标和路径分布，只能通过移动和局部感知信息并记录下来的手段来重建地图)，完成我们派遣机器人对该领域探险的目的。注意，地图中路线是假想路径,可能导致闭合或不可到达。3) 尝试使用最省能量的方法再次遍历所有目标点。
