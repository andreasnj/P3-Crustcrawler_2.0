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
