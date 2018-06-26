//==========================
При перемещении проекта нужно редактировать запись в файле "thermo.pro.user"
<value type="QString" key="ProjectExplorer.BuildConfiguration.BuildDirectory">
/home/walery/qt_example/examples/build-thermo-myKit-Debug
</value>
или удалить этот файл и при открытии проекта он будет создан.
///=========================

Логи термодатчика помещаются в раздел ~/tmp (пример: thermo-120518-231417.log),
где 120518 - текущая дата, как число-месяц-год
231417 - время, как час-минут-секунд

//TODO 
Сигнал об изменении status 
 - отправитель - plotter  -- получатель CoordinatusWindow
 -- для пересчёта в миллиметры вызвать Controller
 
 [GConsole]
 - отправитель - поток GConsole - получатель GConsole
 - отправитель - polotter -- получатель GConsole.