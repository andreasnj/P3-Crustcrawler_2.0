
float m_motor 0.5; //mass of the motor [kg]
float m_link = 0.1; //mass of the link [kg]
float l = 0.15; //length of link [m]
float CoM = l*0.75; //centre of mass, distance from joint [m]
float I_link = m_link*l*l/3; //moment of inertia from link [kg*m^2]
float I_motor = ; //moment of inertia from motor at the end of the link. I_end=I_centre+m*d^2

float 
