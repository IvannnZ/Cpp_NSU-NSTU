# Работа с памятью, выполнение программ [ссылка на урок](https://www.youtube.com/watch?v=TajLTcjBgIg&list=PLlb7e2G7aSpTFea2FYxp7mFfbZW-xavhL&index=3)

## Есть 2 Арихитектуры, 
* гарвардская архитектура(быстрее)
  * команды и память лежать в разных местах
* фон неймана(дешевле)
  * команды и данные это одно и тоже
* есть гибриды, по типу L1 кэш в процессоре

# Процессы и потоки

* Процесс - ресурсы:
  * адресное пространство(память)
  * объекты ядра(файловые дискрипторы, объекты, синхронизации, сокеты)
* Поток - выполнение инструкций
  * Последовательность команд
  * стек
  * Thread Local Storage (TLS) (данные этого потока)
  * Общие ресурсы

//9.05