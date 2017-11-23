

float m_MX28TR = 0.072; //mass of the motor [kg]
float m_MX64T = 0.126; 
float m_MX106T = 0.153;
float m_link = 0.05; //mass of the link [kg]
float l = 0.15; //length of link [m]
float CoM = l*0.75; //centre of mass, distance from joint [m]
float I_link = m_link*l*l/3; //moment of inertia from link [kg*m^2]
float I_motor = ; //moment of inertia from motor at the end of the link. I_end=I_centre+m*d^2