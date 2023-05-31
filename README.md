# Queue Analyser 
Queue Analyser – сервис, предназначенный для сканирования видеопотока с камер внутреннего наблюдения для предоставления
информации о числе людей в заведении.

Доступ к сервису можно получить через сайт или телеграм бота. После сборки и запуска, backend сервер станет доступен по адресу
http://0.0.0.0:8080, а бот будет доступен [по ссылке](https://t.me/queue_analyser_bot).

В качестве frontend части используется React. Репозиторий с ним находится [здесь](https://github.com/TimofeyTst/queue_analyser_front) 

----------------------------------------------------------------
## Настройка телеграм бота
Для запуска телеграм бота в директорию `configs` требуeтся добавить файл `tg_bot_token.json` вида
```
{ "token": "<Токен телеграм бота>" }
```
## Запуск проекта через докер
```
    docker-compose up
```
> Дополнительные настройки: исполняемый файл ./queueAnalyser внутри контейнера принимает параметры, чтобы их использовать нужно добавить внутрь docker-compose.yml устройство веб-камеры (закомментированные строчки), и изменить команду запуска, дописав после ./build/queueAnalyser параметры:
> - Для запуска с визуализацией, указываем индекс визуализации: ```./build/queueAnalyser 0```
> - Для открытия веб-камеры ```./build/queueAnalyser -v```
> - Для открытия веб-камеры с указанием индекса визуализации```./build/queueAnalyser -v 0```
----------------------------------------------------------------
## Запуск проекта через cmake
### 1. Открыть src/const.cpp
### 2. Изменить переменную DOC_ROOT на ".."
> ```DOC_ROOT = "/app"``` => ```DOC_ROOT = ".."```
### 3. Сборка
```
    mkdir build
    cd build
    cmake ..
    make
```
### 4. Запустить можно отдельно
- Cервер ```./start_server```
- Телеграм Бот ```./tgBot```
- Компьютерное зрение ```./queueAnalyser``` 
> ./queueAnalyser принимает параметры
> - Для запуска с визуализацией, указываем индекс визуализации: ```./queueAnalyser 0```
> - Для открытия веб-камеры ```./queueAnalyser -v```
> - Для открытия веб-камеры с указанием индекса визуализации```./queueAnalyser -v 0```


## Подробнее о проекте



---

*Данный проект является выпускной работой по курсу "Программирование на современном C++" в технопарке VK Образование МГТУ им. Баумана*

*Проект выполнила команда **Look@Eat***
