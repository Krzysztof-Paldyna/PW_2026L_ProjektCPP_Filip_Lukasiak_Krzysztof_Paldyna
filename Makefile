
CXX = g++
CXXFLAGS =  -O2


LIBS = -lsfml-graphics -lsfml-window -lsfml-system


OBJS = main.o Battle.o Card.o Enemy.o Player.o \
       graphics_object_end_turn.o graphics_object_character.o \
       graphics_object_card.o \
       graphics_object_energy_counter.o graphics_object_deck_info.o \
       graphics_object_menu_button.o GameMaster.o \
       graphics_object_choose_character.o graphics_object_damage_val.o


TARGET = SlayTheSpire



all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o $(TARGET)

.PHONY: all clean