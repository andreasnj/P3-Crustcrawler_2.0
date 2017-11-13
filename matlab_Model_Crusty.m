DH parameters and representation of forward kinematics%%
L(1) = Link('alpha', 0,'a', 0,'d', 60, 'modified'); %rotational
L(2) = Link('alpha', 90,'a', 0,'d', 0, 'modified'); %rotational
L(3) = Link('alpha', 0,'a', 220, 'd', 0,'modified');%rotational
L(4) = Link('alpha', -90,'a', 270,'d', 0, 'modified');%rotational
crusty=SerialLink(L, 'name', 'CrustcralweProSeries');
%this is needed becauise we have a parismatic jointv - dont ask why!!
%crusty.plotopt = {'workspace' [-700,700,-700,700,-700,700]};
%L(3).qlim=[-1000,1000];
crusty.teach

% ========================================================================
% Authors: © Dimitris Chrysostomou/OleMadsen - AAU-MTECH
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ADEPT Cobra s600
DH parameters and representation of forward kinematics%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% alpha a d theta offset modified D&H
L(1) = Link('alpha', 0,'a', 0,'d', 342, 'modified'); %rotational
L(2) = Link('alpha', 0,'a', 325,'d', 0, 'modified'); %rotational
L(3) = Link('alpha', 0,'a', 275, 'theta', 0,'offset',-165,'modified');%prismatic
L(4) = Link('alpha', 0,'a', 0,'d', 0, 'modified');%rotational
cobra=SerialLink(L, 'name', 'AdeptCobras600');
%this is needed becauise we have a parismatic jointv - dont ask why!!
cobra.plotopt = {'workspace' [-700,700,-700,700,-700,700]};
L(3).qlim=[-1000,1000];
cobra.teach