# paint

Инструкция по сборке

Требования

	•	CMake 3.16+
	•	Qt 5.15+ (добавьте в PATH)
	•	Компилятор (Clang/GCC)
	•	Ninja (опционально)

Сборка

	1.	Склонируйте проект:

git clone https://github.com/PishaBok/paint.git
cd paint


	2.	Создайте папку сборки и перейдите в неё:

mkdir build && cd build


	3.	Настройте проект:

cmake .. -G "Ninja" -DCMAKE_PREFIX_PATH=/path/to/Qt


	4.	Соберите проект:

cmake --build .


	5.	Запустите исполняемый файл:

./Paint

