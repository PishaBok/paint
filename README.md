# paint

Инструкция по сборке

Требования

	•	CMake 3.16+
	•	Qt 5.15+ (добавьте в PATH)
	•	Компилятор (Clang/GCC)
	•	Ninja (опционально)

### Сборка

Склонируйте проект:

	git clone https://github.com/PishaBok/paint.git
	cd paint


Создайте папку сборки и перейдите в неё:

	mkdir build && cd build


Настройте проект:

	cmake .. -G "Ninja" -DCMAKE_PREFIX_PATH=/path/to/Qt


Соберите проект:

	cmake --build .


Запустите исполняемый файл:

	./Paint

