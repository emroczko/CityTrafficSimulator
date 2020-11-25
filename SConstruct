Program('CityTrafficSimulator', Glob('*.h'), Glob('*.cpp'))





env = Environment(CPPPATH='/usr/include')
env.Program('SFMLApp',['source1.cpp', 'source2.cpp', 'source3.cpp'], LIBS = ['sfml-window','sfml-system','sfml-graphics', 'GLU', 'GL'], LIBPATH = ['/usr/lib', '/usr/local/lib'])