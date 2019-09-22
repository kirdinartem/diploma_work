# MadDrive project

## How to start (preinstallation)

1. Clone repo with `git clone --recursive ...` (to fetch submodules)
2. Install all dependencies with `install_pkgs.sh`
3. Install all python modules with `requirements.txt` (`pip install -r requirements.txt`)

> Don't forget to do `git submodule update --init` along with `git pull` to get updates of submodules 

## Requirements

- [ROS Melodic](http://wiki.ros.org/melodic)
- Python 2.7.x

## Contents of repository

- `wr8_description` - описание моделей робота для симуляции в Gazebo
- `wr8_ai` - ПО для распознавания разметки и знаков (на доработке)
- `wr8_gui_server` - backend (серверная часть) для коммуникации с фронтом на Android (закрыто - переименова package.xml)
- `wr8_msgs` - свои типы сообщений и сервисов 
- `wr8_software` - основные скрипты и launch-файлы проекта

Дополнительные пакеты, добавленные как подмодули:
- [ydlidar](https://github.com/EAIBOT/ydlidar) - драйвер для используемого лидара
- [hector_slam](http://wiki.ros.org/hector_slam) - пакет метода hector_slam со всеми сопутствующими
- [teb_local_planner](http://wiki.ros.org/teb_local_planner) - локальный планнер, который рассчитывает локальный маршрут с учетом минимального радиуса поворота (то ,что требуется для автомобилей)
- [rosserial](http://wiki.ros.org/rosserial) - пакет коммуникации по последовательному интерфейсу (Serial)
- `ackermann_controller` - драйвер, который является связующим звеном между Gazebo и ROS топиками (нужен только для симулятора машинки)

> Стягиваются и собираются они по причине совместимости или наличия в репозиториях (некоторых пакетов нет, а некоторые не работают при скачивании через `apt`).

Остальные:
- `controller_wr_driver` - firmware для контроллера WR, stack: ChibiOS for STM32
- `math_task` - решение математической задачи по программирования с Autonet2019
- `install_pkgs.sh` - скрипт установки и скачивания всех необходимых зависимостей
- `requirements.txt` - список Python пакетов для работы

> Все остальные файлы и папки не требуются для работы или будут удалены в скором времени

## Принцип подмены симуляцией

В основе данного принципа лежит возможность работы как с машинкой, так и с симулятором не изменяя основной составляющих и каналов базового стека:

<p align="center">
<img src="asserts/full_scheme.png">
</p>

## Start notes

Наиболее важные места:
- [wr8_description/launch](wr8_description/launch) - основные скрипты  системы симуляции: загрузка и запуск модели, запуск контроллера `ackermann_controller`
- [wr8_description/config](wr8_description/config) - конфигурация контроллера `ackermann_controller`
- [wr8_description/rviz](wr8_description/rviz) - настроенные параметры Rviz для просмотра модели
- [wr8_description/urdf](wr8_description/urdf) - описание модели zaWRka для симуляции
- [wr8_description/worlds](wr8_description/worlds) - "миры" для Gazebo, описание карт, в которых может производиться симуляция
---
- [wr8_software/launch](wr8_software/launch) - все скрипты, которые решают различные задачи и используются как в симуляции, так и на реальном роботе (по принципу подмены симуляцией)
    - [rviz_localization_view](wr8_software/launch/rviz_localization_view.launch), [rviz_slam_view](wr8_software/launch/rviz_slam_view.launch) - скрипты для просмотра информации в Rviz при решении задач SLAM/локализации
    - [keyboard_control](wr8_software/launch/keyboard_control.launch) - управление роботом с клавиатуры
    - [debug_launch](wr8_software/launch/debug_launch.launch), [base_launch](wr8_software/launch/base_launch.launch) - запуск всех систем на реальном роботе в рабочем и отладочном режиме (разделено на два скрипта для сохранения настройки рабочего режима)
    - [slam](wr8_software/launch/slam.launch) - запуск узлов для управления роботом и решения задачи SLAM (не включает в себя подключение к роботу/запуск симулятора)
    - [localization](wr8_software/launch/localization.launch) - запуск узлов для управления роботом и решения задачи локализации на известной карте (не включает в себя подключение к роботу/запуск симулятора)
- [wr8_software/launch/gazebo](wr8_software/launch/gazebo) - скрипты для запуска модели с симуляцией для решения задач SLAM и локализации
- [wr8_software/launch/base](wr8_software/launch/base) - более "базовые" скрипты, которые используются как в симуляции, так и на реальном роботе (по принципу подмены симуляцией)
- [wr8_software/config](wr8_software/config) - конфигурации [move_base](http://wiki.ros.org/move_base) для стека навигации (более подробно: http://wiki.ros.org/navigation/Tutorials/RobotSetup)
- [wr8_software/calib](wr8_software/calib) - калибровочные данные камер (**устарело - надо обновить**)
- [wr8_software/maps](wr8_software/maps) - готовые карты, которые использует [map_server](http://wiki.ros.org/map_server) для представления и решения задачи локализации
- [wr8_software/params](wr8_software/params) - директория с сохраненными параметрами работы (**устарело - надо обновить**)
- [wr8_software/rviz](wr8_software/rviz) - сохраненные параметры представлений Rviz
- [wr8_software/scripts](wr8_software/scripts) - папка со скриптами для Python
- [wr8_software/stereo_config](wr8_software/stereo_config) - конфигурации [move_base](http://wiki.ros.org/move_base) для стека навигации при работе со стереокамерой (**надо обновить**) 

## Some information

Проект под командной разработкой, направленный на участие в ежегодных соревнованиях Profest AutoNet 18+  

Некоторые [правила оформления](https://github.com/serykhelena/AutoNetChallenge/blob/develop/controller_wr_driver/docs/dev_rules.md)

[Регламент соревнований 2019](http://russianrobotics.ru/upload/iblock/039/039d37ea649e49ed2f50210e415bdd6c.pdf)

[Форум, посвящённый вопросам по регламенту](http://www.russianrobotics.ru/forum/forum12/59-autonet-18_.-reglamenty-sezona-2018_19)

[Список участников](https://docs.google.com/spreadsheets/d/e/2PACX-1vQQ2zzrAAbFCBXrUEgEfghzuqSvDOwywB9XMI6uXnDfj5rw4qsn_r54UXMksgU4Eq0onv_xA9ydmw2O/pubhtml?gid=363203216&single=true)

Полезные ссылки:
* [F767ZI Reference manual (RM)](http://www.st.com/content/ccc/resource/technical/document/reference_manual/group0/96/8b/0d/ec/16/22/43/71/DM00224583/files/DM00224583.pdf/jcr:content/translations/en.DM00224583.pdf)
* [F767ZI Datasheet (DS)](http://www.st.com/content/ccc/resource/technical/document/datasheet/group3/c5/37/9c/1d/a6/09/4e/1a/DM00273119/files/DM00273119.pdf/jcr:content/translations/en.DM00273119.pdf)
* [F767ZI Nucleo pinout](https://os.mbed.com/platforms/ST-Nucleo-F767ZI/)
---
* [F767ZI Alternate functions](http://www.st.com/content/ccc/resource/technical/document/datasheet/group3/c5/37/9c/1d/a6/09/4e/1a/DM00273119/files/DM00273119.pdf/jcr:content/translations/en.DM00273119.pdf#page=89)
* [F767ZI Pins assignment (+analogs)](http://www.st.com/content/ccc/resource/technical/document/datasheet/group3/c5/37/9c/1d/a6/09/4e/1a/DM00273119/files/DM00273119.pdf/jcr:content/translations/en.DM00273119.pdf#page=65)
* [F767ZI Timer triggers](http://www.st.com/content/ccc/resource/technical/document/reference_manual/group0/96/8b/0d/ec/16/22/43/71/DM00224583/files/DM00224583.pdf/jcr:content/translations/en.DM00224583.pdf#page=452)
