# Scenario_X
Scenario X, 2nd Year UCL EEE, Real-Time Audio Descrambler Project  
December 2016

The group Scenario project to build a real-time audio descrambler, which has both digital and analog part. The final design used MSP432 programmed in C and some anlogue circuits including a biasing circuit, an 8-bit DAC and a anti-aliasing circuit.

## Purpose
"A gang of criminals are planning to rob a security van carrying a large amount of gold.  To ensure their plan will succeed, they have been practising their act before the planned robbery.  They are concerned that the police might discover their secret plan because they communicate with each other over insecure telephone lines.  
To stop the police from intercepting their communication, they ask Professor Peach, who is a computer expert with a particular interest in traffic control systems, to find a way to secure their telephone conversations.  Professor Peach proposes to make a number of audio scramblers to scramble the telephone conversations so even if the police intercept their communication, the audio message will still be unintelligible.  
However, Professor Peach has himself been arrested by the police for his lewd act in public shortly before the planned robbery.  At Professor Peach’s home, the police find a highly sophisticated audio scrambler and a recorded scrambled message.  When the police replay the scrambled message, they cannot understand it at all because it is scrambled and Professor Peach is not collaborating with the police. They need your help to descramble the audio message and stop the robbery."


## Workload
1)With the help of the MATLAB, we can study how the audio is being scrambled in the first place. The ways of descrambling can be figured out from here

2)By using the MSP432, we can design the filters we need to do the descrambling and solve the main task digitally.

3)In the end, using the analog components to build the analog circuits to support the speaker so that the audio output can be heard

## Team-member
Jianlai Tian       
Yuqi Xu            
Yuanshunle Qi  
Zhichao Sun     
Zhonghao Shi   
