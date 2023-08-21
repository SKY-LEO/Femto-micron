unit main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, JvTrayIcon, JvComponentBase, ImgList, Registry,
  Menus, StdCtrls, XPMan, ExtCtrls, jpeg, JvExControls, JvPoweredBy,
  shellapi, JvExExtCtrls, MMSystem, iaRS232, Vcl.ExtDlgs, pngimage,
  ShlObj, IdAuthentication, IdBaseComponent, IdComponent, IdTCPConnection,
  IdTCPClient, IdHTTP, IdIOHandler, IdIOHandlerSocket, IdIOHandlerStack, IdSSL,
  IdSSLOpenSSL, IdMultipartFormData, System.DateUtils, About_f;

type
  TForm1 = class(TForm)
    IdHTTP1: TIdHTTP;
//    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

//Здесь необходимо описать класс TMyThread:
  TMyThread = class(TThread)
    private
    { Private declarations }
  protected
    procedure Execute; override;
  end;

  TmainFrm = class(TForm)
    MyTray: TJvTrayIcon;
    TrayMenu: TPopupMenu;
    AutoStartupBtn: TMenuItem;
    ExitBtn: TMenuItem;
    AboutBtn: TMenuItem;
    XPManifest1: TXPManifest;
    MessTmr: TTimer;
    TextColorBtn: TMenuItem;
    BlackBtn: TMenuItem;
    WhiteBtn: TMenuItem;
    GreenBtn: TMenuItem;
    BlueBtn: TMenuItem;
    FuchsiaBtn: TMenuItem;
    ImageList1: TImageList;
    Panel2: TPanel;
    Panel3: TPanel;
    Label15: TLabel;
    Label18: TLabel;
    Image1: TImage;
    Label21: TLabel;
    Label1: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label25: TLabel;
    Panel1: TPanel;
    Panel4: TPanel;
    Label2: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Button1: TButton;
    Label6: TLabel;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    N1: TMenuItem;
    AlarmEnableBtn: TMenuItem;
    N10001: TMenuItem;
    Label7: TLabel;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    Timer1: TTimer;
    PortSub: TMenuItem;
    COM11: TMenuItem;
    COM21: TMenuItem;
    COM31: TMenuItem;
    COM41: TMenuItem;
    COM51: TMenuItem;
    Voltage: TLabel;
    Image2: TImage;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Timer2: TTimer;
    Timer3: TTimer;
    ComboBox1: TComboBox;
    Button2: TButton;
    SavePictureDialog1: TSavePictureDialog;
    IdHTTP1: TIdHTTP;
    Timer4: TTimer;
    RUSENG1: TMenuItem;
    Button3: TButton;
    SaveDialog1: TSaveDialog;
    units: TMenuItem;
    CloseTimer: TTimer;
    small_graph_timer: TTimer;
    HW_Label: TLabel;
    Com_detect: TTimer;
    Auto1: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ExitBtnClick(Sender: TObject);
    procedure OKBtnClick();
    procedure AutoStartupBtnClick(Sender: TObject);
    procedure MessTmrTimer(Sender: TObject);
    procedure BlackBtnClick(Sender: TObject);
    procedure WhiteBtnClick(Sender: TObject);
    procedure GreenBtnClick(Sender: TObject);
    procedure BlueBtnClick(Sender: TObject);
    procedure FuchsiaBtnClick(Sender: TObject);
    procedure RedBtnClick(Sender: TObject);
    procedure YellowBtnClick(Sender: TObject);
    procedure SilverBtnClick(Sender: TObject);
    procedure AquaBtnClick(Sender: TObject);
    procedure OliveBtnClick(Sender: TObject);
    procedure MyTrayDoubleClick(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure MyTrayClick(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button1Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure AboutBtnClick(Sender: TObject);
    procedure AlarmEnableBtnClick(Sender: TObject);
    procedure N10001Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure COM11Click(Sender: TObject);
    procedure COM21Click(Sender: TObject);
    procedure COM31Click(Sender: TObject);
    procedure COM41Click(Sender: TObject);
    procedure COM51Click(Sender: TObject);
    procedure Load_stat_btnClick();
    procedure Timer2Timer(Sender: TObject);
    procedure Draw_massive();
    procedure Timer3Timer(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Image2Click(Sender: TObject);
    procedure Timer4Timer(Sender: TObject);
    procedure RUSENG1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure unitsClick(Sender: TObject);
    procedure CloseTimerTimer(Sender: TObject);

    procedure Receive_current_data();

    function Convert_to_usv(mkr: uint32): string;
    procedure small_graph_timerTimer(Sender: TObject);
    procedure Com_detectTimer(Sender: TObject);
    procedure Auto1Click(Sender: TObject);

     private
    fBuf: TiaBuf;
    fBufCount: Integer;
    procedure DoOnReceiveEvent(Sender: TObject; Const aData: TiaBuf;
      aCount: Cardinal);
    procedure DoOnSendedEvent(Sender: TObject; Const aData: TiaBuf;
      aCount: Cardinal);


    { Private declarations }
 protected
  public
    RS232: TiaRS232;
    procedure RefreshRAD;
    procedure SaveReg;
    function GetMyVersion:uint;
    function PosR2L(const FindS, SrcS: string): Integer;
    procedure MakeIcon(f_fon: ulong);
    procedure WMPowerBroadcast(var MyMessage: TMessage); message WM_POWERBROADCAST;
    procedure WMSysCommand(var Message:TMessage);        message WM_SYSCOMMAND;
end;

var
  Need_build: string = '14 Mar 2016';
  mainFrm: TmainFrm;
  MyThread: TMyThread;
  FeatureReportLen: integer = 0;
  DevPresent: boolean = false;
  DenyCommunications: boolean = false;
  pingback: integer;
  AutoStartup: boolean = true;
  AlarmEnable: boolean = true;
  alarmlevel: ulong = 40;
  needexit: boolean = false;
  tempcol: TColor = clLime;
  Fon_units: string;
  bmp:TBitmap;
  png: TPNGObject;
  count_validate_percent: uint;
  IMPS: uint = 0;
  Fon: ulong = 0;
  time_offset_device: uint = 0;
  count_validate: uchar = 0;
  count_interval: uchar = 0;
  blinker: boolean;
  calibration_data: array[0..20] of string;
  EEPROM_data: array[0..100] of uint;
  impps: array[0..61] of uint;
  fonps: array[0..61] of ulong;
  fonpermin: array[0..61] of ulong;
  divgraphminute: ulong =1;
  fonperhour: array[0..25] of ulong;
  divgraphhour: ulong =1;
  fonpm: ulong;
  fonpmm: ulong;
  divgraphimp: uint = 3;
  dosefull: ulong;
  doseday: ulong;
  doseadd: ulong;
  i: uchar;
  temperature: uchar;
  tempsign: boolean;
  divgraph: ulong =6;
  graph_x: uint;
  graph_y: uint;
  graph_y2: uint;
  g_color: uint;
  d_second: uchar = 0;
  d_minute: uchar = 0;
  d_hour: uchar = 0;
  d_day: ulong = 0;
  maxfon: ulong = 0;
  serial_active:  boolean = false;
  comport_number_select: uint = 6;
  comport_number: uint = 1;
  USB_massive_loading: boolean = false;
  Licensed_state: boolean = false;

  max_address: uint = 8640;

  max_fon_massive: array[0..8640] of UInt32;
  doze_massive: array[0..8640] of UInt32;
  selected_point_massive: uint;

  device_serial_0:UInt32;
  device_serial_1:UInt32;
  device_serial_2:UInt32;

  max_fon_massive_ready: array[0..8640] of boolean;
  doze_massive_ready: array[0..8640] of boolean;

  geiger_seconds_count: uint32 = 1;
  address: UInt32 = 0;
  address_last: UInt32 = 0;
  lang_settings:  boolean = false;
  usb_send_try: UInt32 = 0;
  time_offset:uint32;
  myDate : TDateTime;
  formattedDateTime : string;
  Voltage_level: Integer;
  date_sent_flag:  boolean = false;

  firmware_date: string;
  hardware_version: string;

mkr_lang: string =       ' мкР';
mkr2_lang: string =      ' мкР/ч';
mkr3_lang: string =      'мкР/ч]';

mkzv_lang: string =       ' мкЗв';
mkzv2_lang: string =      ' мкЗв/ч';
mkzv3_lang: string =      'мкЗв/ч]';

dos_off_lang: string =   'Дозиметр не подключен';
normal_lang: string =    '[ нормальный фон ]';
high_lang: string =      '[ повышенный фон ]';
danger_lang: string =    '[ ОПАСНЫЙ ФОН ]';
imps_lang: string =      'Имп.';
ZA_lang: string =        'За ';
day_lang: string =       ' дней ';
hour_lang: string =      ' часов ';
minute_lang: string =    ' минут,';
summary_lang: string =   'суммарная доза: ';
maxi_lang: string =      'Максимальный фон: ';
error_lang: string =     'Ошибка:';
curr_lang: string =      'Текущий фон:';
alarm_lang: string =     'Тревога [';
dosi_name_lang: string = 'Ультра-Микрон ';
avg_lang: string =       'Средний фон ';
maxi2_lang: string =     'Максимальный фон ';
avg2_lang: string =      'Средний фон 0 мкР/ч';
maxi3_lang: string =     'Максимальный фон 0 мкР/ч';
avg2zv_lang: string =    'Средний фон 0 мкЗв/ч';
maxi3zv_lang: string =   'Максимальный фон 0 мкЗв/ч';
time_lang: string =      'Время ';
hours2_lang: string =    ' час(ов)   ';
minutes2_lang: string =  ' минут';
alarm2_lang: string =    'ТРЕВОГА!';
fonmax_lang: string =    'Фон более ';
voltage_lang: string =   'Напряжение АКБ: ';
loading_lang: string =   'Загрузка...';


implementation

{$R *.dfm}
{$R sounds.res}
uses Unit1;


procedure TMyThread.Execute;
var
 AIdHTTP: TIdHTTP;
 reg: TRegistry;
 key: String;
 data: TIdMultiPartFormDataStream;
 ix: uint32;

begin
 reg := TRegistry.Create;                              // Открываем реестр
 reg.RootKey := HKEY_CURRENT_USER;
 reg.OpenKey('Software\Micron\Ultra-Micron', false);
 key := reg.ReadString('Reg_key');
 reg.CloseKey;                                          // Закрываем раздел
 if key <> '' then
 begin
   data := TIdMultiPartFormDataStream.Create;
   AIdHTTP := TIdHTTP.Create(nil);
   AIdHTTP.HandleRedirects := true;
   try
     // добавляем нужные параметры
     for ix := 0 to max_address-1 do begin
       if doze_massive[ix]>0 then
       if(geiger_seconds_count>600) then begin
         data.AddFormField(IntToStr(ix), IntToStr((((doze_massive[ix]+doze_massive[ix+1]) * geiger_seconds_count) Div 1200)));
       end
       else begin
         data.AddFormField(IntToStr(ix), IntToStr(((doze_massive[ix] * geiger_seconds_count) Div 600)));
       end;
     end;
     AIdHTTP.Post(Concat('http://upload.xn--h1aeegel.net/upload.php?id=',key,'&devoffset=',Inttostr(time_offset_device)), data);
   except
    begin
    end;
   end;
   AIdHTTP.Disconnect;
   AIdHTTP.Free;
   data.Free;
 end;
end;

function TmainFrm.PosR2L(const FindS, SrcS: string): Integer;
{Функция возвращает начало последнего вхождения
 подстроки FindS в строку SrcS, т.е. первое с конца.
 Если возвращает ноль, то подстрока не найдена.
 Можно использовать в текстовых редакторах
 при поиске текста вверх от курсора ввода.}

  function InvertS(const S: string): string;
    {Инверсия строки S}
  var
    i, Len: Integer;
  begin
    Len := Length(S);
    SetLength(Result, Len);
    for i := 1 to Len do
      Result[i] := S[Len - i + 1];
  end;

var
  ps: Integer;
begin
  {Например: нужно найти последнее вхождение
   строки 'ро' в строке 'пирожок в коробке'.
   Инвертируем обе строки и получаем
     'ор' и 'екборок в кожорип',
   а затем ищем первое вхождение с помощью стандартной
   функции Pos(Substr, S: string): string;
   Если подстрока Substr есть в строке S, то
   эта функция возвращает позицию первого вхождения,
   а иначе возвращает ноль.}
  ps := Pos(InvertS(FindS), InvertS(SrcS));
  {Если подстрока найдена определяем её истинное положение
   в строке, иначе возвращаем ноль}
  if ps <> 0 then
    Result := Length(SrcS) - Length(FindS) - ps + 2
  else
    Result := 0;
end;



/////////////////////////////////////////////////////
function TmainFrm.GetMyVersion:uint;
type
  TVerInfo=packed record
    Nevazhno: array[0..47] of byte; // ненужные нам 48 байт
    Minor,Major,Build,Release: word; // а тут версия
  end;
var
  s:TResourceStream;
  v:TVerInfo;
begin
  result:=0;
  try
    s:=TResourceStream.Create(HInstance,'#1',RT_VERSION); // достаём ресурс
    if s.Size>0 then begin
      s.Read(v,SizeOf(v)); // читаем нужные нам байты
      result:=v.Build;
    end;
  s.Free;
  except; end;
end;

// =============================================================================
procedure TmainFrm.Receive_current_data;
var
  ia:uint;
begin

  Fon :=0;
  IMPS :=0;

  count_validate := 0;
  count_interval := 0;
  IMPS := (fBuf[1] shl 8)+fBuf[2]; // собираем 2 чара
  Fon := ((fBuf[3] shl 16)+(fBuf[4] shl 8))+fBuf[5]; // собираем 3 чара
  Voltage_level := (fBuf[6]+300) *10; // собираем 2 чара
  count_validate := 0;
  count_interval := 30;

  // обработчик тревоги
  if (alarmenable and (fon > alarmlevel) and (d_minute mod 2 = 0) and (d_second mod 10 = 0)) then
  begin
    if(mainfrm.units.Checked = true) then
    begin MyTray.BalloonHint(alarm2_lang,fonmax_lang+Convert_to_usv(alarmlevel)+mkzv2_lang,TBalloonType(3),5000,true); end
    else  MyTray.BalloonHint(alarm2_lang,fonmax_lang+IntToStr(alarmlevel)+mkr2_lang,TBalloonType(3),5000,true);
    PlaySound('alarm', hInstance, SND_RESOURCE);
  end;

  // обработчик тревоги
  if maxfon < fon then maxfon:=fon;

  // вычисляем пределы импульсов
  impps[0] := impps[0]+IMPS;


//  Licensed_state:=true;
  Label15.Caption := Convert_to_usv(fon);
  Label18.Caption := fon_units;

  if count_interval >0 then count_validate_percent := (100*(count_interval-count_validate)) div count_interval;


end;
// =============================================================================



// =============================================================================
function TmainFrm.Convert_to_usv(mkr: uint32): string;
var
  float : Double;
begin
  if(mainfrm.units.Checked = true) then
  begin
    float:=mkr*0.0098;
    result := FloatToStrF(float,ffFixed,8,2);
    if (lang_settings=false) then
    begin
      mainfrm.BlackBtn.Caption:=  '0.24 uSv/h';
      mainfrm.WhiteBtn.Caption:=  '0.39 uSv/h';
      mainfrm.GreenBtn.Caption:=  '1.18 uSv/h';
      mainfrm.BlueBtn.Caption:=   '3.92 uSv/h';
      mainfrm.FuchsiaBtn.Caption:='9.80 uSv/h';
      mainfrm.N10001.Caption:=   '29.40 uSv/h';
    end else begin
      mainfrm.BlackBtn.Caption:=  '0.24 мкЗв/ч';
      mainfrm.WhiteBtn.Caption:=  '0.39 мкЗв/ч';
      mainfrm.GreenBtn.Caption:=  '1.18 мкЗв/ч';
      mainfrm.BlueBtn.Caption:=    '3.9 мкЗв/ч';
      mainfrm.FuchsiaBtn.Caption:='9.80 мкЗв/ч';
      mainfrm.N10001.Caption:=   '29.40 мкЗв/ч';
    end;
  end else begin
    result := IntToStr(mkr);
    if (lang_settings=false) then
    begin
      mainfrm.BlackBtn.Caption:=    '25 uR/h';
      mainfrm.WhiteBtn.Caption:=    '40 uR/h';
      mainfrm.GreenBtn.Caption:=   '120 uR/h';
      mainfrm.BlueBtn.Caption:=    '400 uR/h';
      mainfrm.FuchsiaBtn.Caption:='1000 uR/h';
      mainfrm.N10001.Caption:=    '3000 uR/h';
    end else begin
      mainfrm.BlackBtn.Caption:=    '25 мкР/ч';
      mainfrm.WhiteBtn.Caption:=    '40 мкР/ч';
      mainfrm.GreenBtn.Caption:=   '120 мкР/ч';
      mainfrm.BlueBtn.Caption:=    '400 мкР/ч';
      mainfrm.FuchsiaBtn.Caption:='1000 мкР/ч';
      mainfrm.N10001.Caption:=    '3000 мкР/ч';
    end;
  end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.WMSysCommand(var Message: TMessage);
begin
    if Message.WParam = SC_MAXIMIZE then begin
        Load_stat_btnClick();
        Message.Result := 0;
    end else if Message.WParam = SC_MINIMIZE then begin
        OKBtnClick();
        Message.Result := 0;
    end else if Message.WParam = SC_CLOSE then begin
        OKBtnClick();
        Message.Result := 0;
    end else inherited;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.WMPowerBroadcast(var MyMessage: TMessage);
begin
if MyMessage.Msg = WM_POWERBROADCAST then begin
if MyMessage.WParam = PBT_APMRESUMEAUTOMATIC then begin
    DenyCommunications:= false;
end
else begin
    DevPresent:= false;
    firmware_date:='';
    date_sent_flag:=false;
    device_serial_0:=0;
    device_serial_1:=0;
    device_serial_2:=0;
    About_f.About.Edit2.Color := clWhite;

    DenyCommunications:= true;
    RS232.StopListner;
    RS232.Close;
end;
end;
inherited;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.SaveReg;
var
  reg: TRegistry;
  dir:string;
  exe:string;
  f:TextFile;
begin
  reg := TRegistry.Create;                               // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;                      // Для текущего пользователя
  reg.OpenKey('Software\Micron\Ultra-Micron', true); // Открываем раздел
  reg.WriteBool('autorun', AutoStartup);
  reg.WriteBool('alarmenable', AlarmEnable);
  reg.WriteBool('lang', lang_settings);

  if(Licensed_state<>true) then mainfrm.units.Checked:= false; // проверка лицензии
  reg.WriteBool('units', mainfrm.units.Checked);

  reg.WriteInteger('alarmlevel', AlarmLevel);
  reg.WriteInteger('comport',comport_number_select);
  reg.CloseKey;                                          // Закрываем раздел
  reg.OpenKey('Software\Microsoft\Windows\CurrentVersion\Run', true);  // Открываем раздел
  if AutoStartup then begin
    dir:=copy(application.ExeName,1,PosR2L('\',application.ExeName));
    exe:=copy(application.ExeName,PosR2L('\',application.ExeName)+1,40);

    if FileExists(dir+'Micron.cmd') then begin
      AssignFile(f,dir+'Micron.cmd');
      Rewrite(f);
      Writeln(f,'runas /savecred /user:Administrator "'+dir+exe+'"');
      Flush(f);
      CloseFile(f);
      reg.WriteString('Micron', '"'+dir+'Micron.cmd"'); // Если батник загружен
    end else begin
      reg.WriteString('Micron', application.ExeName); // Если не загружен
    end;
  end
  else
  reg.DeleteValue('Micron');                          // или удаляем информацию
  reg.CloseKey;                                          // Закрываем раздел
  reg.Free;
end;
// =============================================================================



// =============================================================================
procedure TmainFrm.MakeIcon(f_fon: ulong);
var
 ii: uint;
begin

  if (not DevPresent) then
    begin
  ImageList1.GetIcon(0,MyTray.Icon);
  MyTray.Hint := dos_off_lang;
    end
    else
    begin


    if(mainfrm.units.Checked = true) then
    begin MyTray.Hint := 'Micron: '+Convert_to_usv(fon)+' '+fon_units;
    end else  MyTray.Hint := 'Micron: '+IntToStr(Fon)+' '+fon_units;

      if ((count_validate >0) and blinker) then
      begin
        ImageList1.GetIcon(1,MyTray.Icon);
        blinker := false;
      end
      else
      begin // cv
        blinker:=true;
        if (Fon < 41) then
        begin
          Panel1.Color := clGreen;
          Label7.Caption := normal_lang;
          ImageList1.GetIcon(2,MyTray.Icon);
        end
        else if (Fon < 121) then
        begin
          Panel1.Color := clOlive;
          Label7.Caption := high_lang;
          ImageList1.GetIcon(3,MyTray.Icon);
        end
        else
        begin
          Panel1.Color := clMaroon;
          Label7.Caption := danger_lang;
          ImageList1.GetIcon(4,MyTray.Icon);
        end;
      end; // cv
    end;

  Image1.Canvas.Brush.Color := clWhite;
  Image1.Canvas.Pen.Color := clWhite;
  Image1.Canvas.Rectangle(4, 0,305,100);
  Image1.Canvas.Pen.Color := clBlack;
  Image1.Canvas.Rectangle(2, 0,3,100);
  Image1.Canvas.Rectangle(0, 98,305,97);

  if RadioButton1.Checked then
begin
// граф ИМПУЛЬСОВ
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (impps[ii]>5) then g_color:=clRED
    else if (impps[ii]>3) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((impps[ii]*95) div divgraphimp)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+4, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+5;
    end;

//      Fon_units := imps_lang;
    Label22.Caption := IntToStr(divgraphimp);
    Label23.Caption := imps_lang;
// граф ИМПУЛЬСОВ
end
else if RadioButton2.Checked then
begin
  // граф фона сек
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (fonps[ii]>120) then g_color:=clRED
    else if (fonps[ii]>40) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((fonps[ii]*95) div divgraph)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+4, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+5;
    end;
    begin
      Fon_units := mkr2_lang;
      if(mainfrm.units.Checked = true) then      Fon_units := mkzv2_lang;
    end;
    Label22.Caption := IntToStr(divgraph);
    Label23.Caption := fon_units;
// граф фона сек
end
else if RadioButton3.Checked then
begin
  // граф фона мин
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (fonpermin[ii]>120) then g_color:=clRED
    else if (fonpermin[ii]>40) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((fonpermin[ii]*95) div divgraphminute)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+4, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+5;
    end;
    begin
      Fon_units := mkr2_lang;
      if(mainfrm.units.Checked = true) then Fon_units := mkzv2_lang;
    end;
    Label22.Caption := IntToStr(divgraphminute);
    Label23.Caption := fon_units;
// граф фона мин
end
else if RadioButton4.Checked then
begin
  // граф фона час
  graph_x:=5;
  graph_y:=96;
    for ii := 1 to 60 do
    begin
    if (fonperhour[ii]>120) then g_color:=clRED
    else if (fonperhour[ii]>40) then g_color:=clYELLOW
    else g_color:=clGREEN;

    graph_y2:=graph_y-((fonperhour[ii]*95) div divgraphhour)-1;
    Image1.Canvas.Pen.Color := g_color;
    Image1.Canvas.Brush.Color := g_color;
    Image1.Canvas.Rectangle(graph_x, graph_y, graph_x+9, graph_y2+1);


    Image1.Canvas.Pen.Color := clBlack;
    Image1.Canvas.Rectangle(graph_x-1, 98,graph_x,100);

    graph_x:=graph_x+12;
    end;
    begin
      Fon_units := mkr2_lang;
      if(mainfrm.units.Checked = true) then      Fon_units := mkzv2_lang;
    end;
    Label22.Caption := IntToStr(divgraphhour);
    Label23.Caption := fon_units;
// граф фона час
end;

// пока уберём    Label3.Caption := '[Датчик] - Импульсов в секунду: '+IntToStr(IMPS);
    Label4.Caption := ZA_lang+IntToStr(d_day)+day_lang+IntToStr(d_hour)+hour_lang+IntToStr(d_minute)+minute_lang;

    if (d_minute > 0) then
    begin
      doseadd := (fonpmm div 60);
    end else doseadd := 0;
    begin
      Label5.Caption := summary_lang+IntToStr(dosefull+doseday+doseadd)+mkr_lang;
        if(mainfrm.units.Checked = true) then
          Label5.Caption := summary_lang+Convert_to_usv(dosefull+doseday+doseadd)+mkzv_lang;
    end;
      Label6.Caption := maxi_lang+IntToStr(maxfon)+mkr2_lang;
        if(mainfrm.units.Checked = true) then
          Label6.Caption := maxi_lang+Convert_to_usv(maxfon)+mkzv2_lang;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.RefreshRAD;
begin
    MakeIcon(Fon);
end;

procedure TmainFrm.RUSENG1Click(Sender: TObject);
begin
lang_settings:=RUSENG1.Checked;
SaveReg;
end;

procedure TmainFrm.FormCreate(Sender: TObject);
var
  reg: TRegistry;
  dir:string;
  exe:string;
  f:textfile;

begin

mainFrm.Caption:='Micron build:'+IntToStr(GetMyVersion);
   Windows.EnableMenuItem( GetSystemMenu( Handle, false ), SC_CLOSE, MF_DISABLED or MF_GRAYED );
   GetSystemMenu( Handle, false );
   Perform( WM_NCPAINT, Handle, 0 );

  Image2.Canvas.Brush.Color := RGB(186, 170, 134);
  Image2.Canvas.Pen.Color := clBlack;
  Image2.Canvas.Rectangle(0,0,Image2.Width, Image2.Height);
  MainFrm.Width:=400;
  RS232 := TiaRS232.Create;
  RS232.OnRSReceived := DoOnReceiveEvent;
  RS232.OnRSSended := DoOnSendedEvent;
  SetLength(fBuf, 64);
  fBufCount := 0;

  //Setting the default value

  MyTray.IconIndex := -1;
  MessTmr.Enabled := true;
  reg := TRegistry.Create;                              // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;
  if reg.OpenKey('Software\Micron\Ultra-Micron', false) then
  begin
    try
      AutoStartup := reg.ReadBool('autorun');
    except
      AutoStartup := false;
    end;
    try
      lang_settings := reg.ReadBool('lang');
    except
      lang_settings := false;
    end;
    try
      comport_number_select := reg.ReadInteger('comport');
    except
      comport_number_select := 6;
    end;
    try
      if (not reg.valueexists('units')) then
        reg.WriteBool('units', false);
      mainfrm.units.Checked := reg.ReadBool('units');
    except
//      mainfrm.units.Checked := false;
    end;
    try
      AlarmEnable := reg.ReadBool('alarmenable');
    except
      AlarmEnable := false;
    end;
    try
      AlarmLevel := reg.ReadInteger('alarmlevel');
    except
      AlarmLevel := 40;
    end;
  end else begin    // если нет раздела -> прога еще не запускалась -> ставим на автозагрузку
    reg.OpenKey('Software\Micron\Ultra-Micron', true);
    AutoStartup := true;
    try
      reg.WriteBool('autorun', AutoStartup);
    except
    end;
    try
      reg.WriteInteger('comport', 1);
    except
    end;
    try
      reg.WriteBool('units', false);
    except
    end;
    try
      reg.WriteBool('lang', false);
    except
    end;
    try
      reg.WriteBool('alarmenable', AlarmEnable);
    except
    end;
    try
      reg.WriteInteger('alarmlevel', AlarmLevel);
    except
    end;
    reg.CloseKey;                                          // Закрываем раздел
    try
      reg.OpenKey('Software\Microsoft\Windows\CurrentVersion\Run', true); // Открываем раздел
    dir:=copy(application.ExeName,1,PosR2L('\',application.ExeName));
    exe:=copy(application.ExeName,PosR2L('\',application.ExeName)+1,40);

    if FileExists(dir+'Micron.cmd') then begin
      AssignFile(f,dir+'Micron.cmd');
      Rewrite(f);
      Writeln(f,'runas /savecred /user:Administrator "'+dir+exe+'"');
      Flush(f);
      CloseFile(f);
      reg.WriteString('Micron', '"'+dir+'Micron.cmd"'); // Если батник загружен    end else begin
    end;
    except
    end;
  end;
  reg.CloseKey;                                        // Закрываем раздел
  reg.Free;
  AutoStartupBtn.Checked := AutoStartup;
  RUSENG1.Checked := lang_settings;
  AlarmEnableBtn.Checked := AlarmEnable;
    if(comport_number_select=1)then COM11.Checked := true;
    if(comport_number_select=2)then COM21.Checked := true;
    if(comport_number_select=3)then COM31.Checked := true;
    if(comport_number_select=4)then COM41.Checked := true;
    if(comport_number_select=5)then COM51.Checked := true;
    if(comport_number_select=6)then Auto1.Checked := true;


  if (lang_settings=false) then
  begin

    mkr_lang:=       ' uR';
    mkr2_lang:=      ' uR/h';
    mkr3_lang:=      'uR/h]';
    mkzv_lang:=       ' uSv';
    mkzv2_lang:=      ' uSv/h';
    mkzv3_lang:=      'uSv/h]';
    dos_off_lang:=   'Dosimeter not connected';
    normal_lang:=    '[ normal radiation level ]';
    high_lang:=      '[ high radiation level ]';
    danger_lang:=    '[ !!! DANGER !!! ]';
    imps_lang:=     'Imp.';
    ZA_lang:=        'On ';
    day_lang:=       ' days ';
    hour_lang:=      ' hours ';
    minute_lang:=    ' minute,';
    summary_lang:=   'Summary dose: ';
    maxi_lang:=      'Maximum peak: ';
    error_lang:=     'Error:';
    curr_lang:=      'radiation level:';
    alarm_lang:=     'ALARM [';
    dosi_name_lang:= 'Ultra-Micron ';
    avg_lang:=       'Avg level ';
    maxi2_lang:=     'Max level ';
    avg2_lang:=      'Avg level 0 uR/h';
    maxi3_lang:=     'Max level 0 uR/h';
    avg2zv_lang:=    'Avg level 0 uSv/h';
    maxi3zv_lang:=   'Max level 0 uSv/h';
    time_lang:=      'Time ';
    hours2_lang:=    ' hours   ';
    minutes2_lang:=  ' minute';
    alarm2_lang:=    'ALARM!';
    fonmax_lang:=    'radiation level up to ';
    voltage_lang:=   'Li-Ion voltage: ';

    Label7.Caption:=       '';
    Label18.Caption:=       '';
    Label2.Caption:=       'Accumulated radiation dose:';
    //Load_stat_btn.Caption:='Load logs';
    //OKBtn.Caption:=        'Hide';
    Button1.Caption:=      'Clear';
    Button2.Caption:=      'Screenshot';
    Button3.Caption:=      'Save to CSV';
    Radiobutton4.Caption:= 'dose/h';
    Radiobutton3.Caption:= 'dose/m';
    Radiobutton2.Caption:= 'dose/s';
    Radiobutton1.Caption:= 'imp/4s';

    N1.Caption:='Dosimeter';
    TextColorBtn.Caption:='Alarm level';
    PortSub.Caption:='COM Port';
    AlarmEnableBtn.Caption:='Enable Alarm';
    AboutBtn.Caption:='About';
    ExitBtn.Caption:='Exit';
    AutoStartupBtn.Caption:='Autostart';
    units.Caption:='uR/uSv';
    loading_lang:='Loading...';

  end

end;
// =============================================================================


// =============================================================================
procedure TmainFrm.CloseTimerTimer(Sender: TObject);
begin
  if (RS232.Active = true) then
    begin
//      DevPresent:=false;
//      date_sent_flag:=false;
//      device_serial_0:=0;
//      device_serial_1:=0;
//     device_serial_2:=0;
//      About_f.About.Edit2.Color := clWhite;
      RS232.StopListner;
      RS232.Close;
      CloseTimer.Enabled:=false;
      CloseTimer.interval:=100;
    end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.COM11Click(Sender: TObject);
begin
comport_number_select:=1;
SaveReg;
COM11.Checked := true;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := false;
Auto1.Checked := false;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.COM21Click(Sender: TObject);
begin
comport_number_select:=2;
SaveReg;
COM11.Checked := false;
COM21.Checked := true;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := false;
Auto1.Checked := false;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.COM31Click(Sender: TObject);
begin
comport_number_select:=3;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := true;
COM41.Checked := false;
COM51.Checked := false;
Auto1.Checked := false;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.COM41Click(Sender: TObject);
begin
comport_number_select:=4;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := true;
COM51.Checked := false;
Auto1.Checked := false;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.COM51Click(Sender: TObject);
begin
comport_number_select:=5;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := true;
Auto1.Checked := false;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.ComboBox1Change(Sender: TObject);
begin
  Draw_massive();
end;


procedure TmainFrm.Com_detectTimer(Sender: TObject);
var
reg : TRegistry;
tstrSubKeys : TStringList;
strParentKey: String;
q:uint;
ixi:uint;
begin
if (Auto1.Checked = true) then
begin
  reg := TRegistry.Create;                              // Открываем реестр
  tstrSubKeys:= TStringList.Create;
  reg.RootKey := HKEY_LOCAL_MACHINE;
  if reg.OpenKey('HARDWARE\DEVICEMAP\SERIALCOMM', False) then begin
    reg.GetValueNames(tstrSubKeys);
    if tstrSubKeys.Count > 0 then
    begin
      q:=tstrSubKeys.Count-1;
      for ixi := 0 to q do
      begin
        if (Pos('USBSER',tstrSubKeys[ixi])>0) then
        begin
          comport_number:= StrToInt(
            Copy(reg.ReadString(
                                tstrSubKeys[ixi]
                                ), 4, 3));
        end;
      end;
    end;
  end;
  reg.CloseKey;
  reg.Free;
  tstrSubKeys.Free;
end else begin
comport_number:=comport_number_select;
end;
end;

// =============================================================================


// =============================================================================
procedure TmainFrm.ExitBtnClick(Sender: TObject);
begin
  if(DevPresent=true) then
   begin
      DevPresent:=false;
      firmware_date:='';
      date_sent_flag:=false;
      device_serial_0:=0;
      device_serial_1:=0;
      device_serial_2:=0;
      About_f.About.Edit2.Color := clWhite;
   end;

  needexit := true; // вежливо просим свалить из памяти
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.OKBtnClick();
begin
  MainFrm.Width:=400;
  Timer2.Enabled:=false;
  MyTray.HideApplication;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Auto1Click(Sender: TObject);
begin
comport_number_select:=6;
SaveReg;
COM11.Checked := false;
COM21.Checked := false;
COM31.Checked := false;
COM41.Checked := false;
COM51.Checked := false;
Auto1.Checked := true;
end;

procedure TmainFrm.AutoStartupBtnClick(Sender: TObject);
begin
  AutoStartup := AutoStartupBtn.Checked;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.MessTmrTimer(Sender: TObject);
var
iz: uchar;
begin
  RefreshRAD;
  // таймер
  fonpm := fonpm+fonps[d_second];
  d_second:=d_second+1;
  if(d_second = 60)then
  begin
  d_second:=0;
    fonpmm := fonpmm + (fonpm div 60);


    fonpermin[0] := fonpm div 60;
    divgraphminute := 1;
    for iz := 60 downto 1 do
    begin
    fonpermin[iz] := fonpermin[iz-1];
    if fonpermin[iz] > divgraphminute then divgraphminute := fonpermin[iz];
    end;
    fonpermin[0] := 0;


    fonpm := 0;
  d_minute:=d_minute+1;
      if (d_minute = 60) then
      begin

    fonperhour[0] := fonpmm div 60;
    divgraphhour := 1;
    for iz := 24 downto 1 do
    begin
    fonperhour[iz] := fonperhour[iz-1];
    if fonperhour[iz] > divgraphhour then divgraphhour := fonperhour[iz];
    end;
    fonperhour[0] := 0;

      d_minute:=0;
      doseday:= doseday + (fonpmm div 60);
      fonpmm := 0;
      d_hour:=d_hour+1;
          if (d_hour=24) then
          begin
          d_hour:=0;
          d_day:=d_day+1;
          dosefull := dosefull + doseday;
          doseday:=0;
          end;
      end;
  end;
  // таймер
    if needexit then
    application.Terminate;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.MyTrayClick(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
if Button <> mbRight then
begin
  if (not DevPresent) then
      MyTray.BalloonHint(error_lang,dos_off_lang,TBalloonType(3),5000,true)
    else
      if(mainfrm.units.Checked = true) then
      begin MyTray.BalloonHint(curr_lang,Convert_to_usv(Fon)+fon_units,TBalloonType(2),5000,true); end
      else  MyTray.BalloonHint(curr_lang,IntToStr(Fon)+      fon_units,TBalloonType(2),5000,true);
end;
    if(mainfrm.units.Checked = true) then
    begin AlarmEnableBtn.Caption := alarm_lang+Convert_to_usv(alarmlevel)+mkzv3_lang; end
    else AlarmEnableBtn.Caption := alarm_lang+IntToStr(alarmlevel)+mkr3_lang;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.N10001Click(Sender: TObject);
begin
   alarmlevel:=3000;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.MyTrayDoubleClick(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  MyTray.ShowApplication;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.N1Click(Sender: TObject);
begin
  MyTray.ShowApplication;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.AlarmEnableBtnClick(Sender: TObject);
begin
  AlarmEnable := AlarmEnableBtn.Checked;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.BlackBtnClick(Sender: TObject);
begin
  alarmlevel:=25;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.WhiteBtnClick(Sender: TObject);
begin
  alarmlevel:=40;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.GreenBtnClick(Sender: TObject);
begin
    alarmlevel:=120;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Image2Click(Sender: TObject);
var
  foo: TPoint;
begin

if selected_point_massive = 0 then
begin
  Timer2.Enabled := False;
  foo:=Image2.ScreenToClient(Mouse.CursorPos);
  selected_point_massive:=((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset;
  Draw_massive();
end
else
begin
   selected_point_massive :=0;
   Timer2.Enabled := True;
   Draw_massive();
end;

end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Load_stat_btnClick();
var
  vAns: TiaBuf;
  ix: uint;
  ibx: uint;
begin

Unit1.Form1.Show;
myDate:=Now;

if (lang_settings=false) then
begin
  Unit1.Form1.Label1.Caption:='Loading maximum radiation array:';
  Unit1.Form1.Label2.Caption:='Loading average radiation array:';
end;

Unit1.Form1.max_fon.Caption:='0%';
Unit1.Form1.impulses.Caption:='0%';
Unit1.Form1.errors.Caption:='0';

for ibx := 0 to max_address do
begin
  max_fon_massive[ibx]:=0;
  doze_massive[ibx]:=0;
  max_fon_massive_ready[ibx]:=false;
  doze_massive_ready[ibx]:=false;
end;


Timer3.Enabled:=false;
Timer3.Interval:=3000;
Timer3.Enabled:=true;
address_last:=max_address;

ComboBox1.Items.Clear;
for ibx := 0 to 59 do
begin
Combobox1.AddItem(DateToStr(Date-ibx), nil);
end;

begin
//  DevPresent:=false;

  RS232.Open;
  RS232.StartListner;
  CloseTimer.Enabled:=false;
  CloseTimer.Interval:=1500;
  CloseTimer.Enabled:=true;

  for ix := 0 to max_address do begin
    doze_massive[ix]:=0;
    max_fon_massive[ix]:=0;
    doze_massive_ready[ix]:=false;
    max_fon_massive_ready[ix]:=false;
  end;

  if (RS232.Active)then
  begin
   DevPresent:=true;

   SetLength(vAns, 5);
   vAns[0]:=$d5; // считать смещение времени
   vAns[1]:=$33; // считать настройки
   vAns[2]:=$39; // выполнить сброс счетчиков дозиметра
   vAns[3]:=$31; // начать загрузку массива
   vAns[4]:=$32; // начать загрузку массива
   RS232.Send(vAns);

   USB_massive_loading:=true;

  end
  else
    Unit1.Form1.Close;
//    Fix_error_now:=false;
  end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.BlueBtnClick(Sender: TObject);
begin
    alarmlevel:=400;
  SaveReg;
end;

procedure TmainFrm.Button1Click(Sender: TObject);
var im:uchar;
begin
dosefull:=0;
doseday:=0;
d_day:=0;
d_hour:=0;
d_minute:=0;
d_second:=0;
maxfon:=0;
fonpmm:=0;
for im := 0 to 61 do fonpermin[im] := 0;
for im := 0 to 25 do fonperhour[im] :=0;

end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Button2Click(Sender: TObject);
begin
 bmp := TBitmap.Create;
 bmp.Width := mainFrm.Width-10;
 bmp.Height := mainFrm.Height-30;
 BitBlt(bmp.Canvas.Handle, 0,0, mainFrm.Width-10, mainFrm.Height-30, GetDC(mainFrm.Handle), 0,0,SRCCOPY);

png := TPNGObject.create;
png.assign(bmp);


SavePictureDialog1.DefaultExt := '.png';
SavePictureDialog1.FileName := dosi_name_lang+Combobox1.Text+'.png';

If SavePictureDialog1.Execute then
   begin
     png.SaveToFile(SavePictureDialog1.fileName);
   end;
bmp.Free;
png.free;

end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Button3Click(Sender: TObject);
var
  F: TextFile;
  FileName: string;
  I: Integer;
  ix: Integer;
  TempStr: string;
  Y, M, D: Word;
begin
  SaveDialog1.DefaultExt := '.csv';
  SaveDialog1.FileName := dosi_name_lang+'.csv';

  If SaveDialog1.Execute then
   begin
   try
    AssignFile(F, SaveDialog1.fileName);  // связали файл с переменной
    Rewrite(F);               // создаем пустой файл
// если строка с заголовком не нужна, то можно эту строку удалить.

    WriteLn(F,
        '"', 'Element'  , '";',
        '"', 'Timestamp', '";',
        '"', 'Avg_Fon'  , '";',
        '"', 'Max_Fon'  , '";',
        '"', 'Units'    , '"');

    for ix := 0 to max_address do begin
     if doze_massive[ix]>0 then begin
       DateTimeToString(formattedDateTime, 'c', IncMinute(IncSecond(myDate, -(4*time_offset_device)), -(10*ix)));
       if(mainfrm.units.Checked = true) then
       begin
         if(geiger_seconds_count>600) then begin
           WriteLn(F,
              '"', IntToStr(ix), '";',
              '"', formattedDateTime,      '";',
              '"', Convert_to_usv((((doze_massive[ix]+doze_massive[ix+1]) * geiger_seconds_count) Div 1200)), '";',
              '"', Convert_to_usv(max_fon_massive[ix]), '";',
              '"', 'uSv/h', '"');
         end
         else begin
           WriteLn(F,
              '"', IntToStr(ix), '";',
              '"', formattedDateTime,      '";',
              '"', Convert_to_usv((doze_massive[ix] * geiger_seconds_count) Div 600), '";',
              '"', Convert_to_usv(max_fon_massive[ix]), '";',
              '"', 'uSv/h', '"');
         end;
      end else
         if(geiger_seconds_count>600) then begin
            WriteLn(F,
              '"', IntToStr(ix), '";',
              '"', formattedDateTime,      '";',
              '"', IntToStr((((doze_massive[ix]+doze_massive[ix+1]) * geiger_seconds_count) Div 1200 )), '";',
              '"', IntToStr(max_fon_massive[ix]), '";',
              '"', 'uR/h', '"');
         end
         else begin
            WriteLn(F,
              '"', IntToStr(ix), '";',
              '"', formattedDateTime,      '";',
              '"', IntToStr((doze_massive[ix] * geiger_seconds_count) Div 600), '";',
              '"', IntToStr(max_fon_massive[ix]), '";',
              '"', 'uR/h', '"');
         end;
       end;
    end;
  finally
    CloseFile(F);
  end;
 end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.FuchsiaBtnClick(Sender: TObject);
begin
    alarmlevel:=1000;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.RedBtnClick(Sender: TObject);
begin
  tempcol := clRed;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.YellowBtnClick(Sender: TObject);
begin
  tempcol := clYellow;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.SilverBtnClick(Sender: TObject);
begin
  tempcol := clSilver;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.small_graph_timerTimer(Sender: TObject);
var
  ia: uint;
begin
  // вычисляем пределы импульсов
  impps[0] := impps[0]+IMPS;
  divgraphimp := 3;
  for ia := 60 downto 1 do //?
  begin
    impps[ia] := impps[ia-1];
    if impps[ia] > divgraphimp then divgraphimp := impps[ia];
  end;
  impps[0] := 0;

  // вычисляем пределы фона
  fonps[0] := fon;
  divgraph := 6;
  for ia := 61 downto 1 do
  begin
    fonps[ia] := fonps[ia-1];
    if fonps[ia] > divgraph then divgraph := fonps[ia];
  end;
  fonps[0] := 0;
  Fon_units := mkr2_lang;
  if(mainfrm.units.Checked = true) then Fon_units := mkzv2_lang;

end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Timer1Timer(Sender: TObject);
var
  vAns: TiaBuf;
  bytes_to_send: uint;
  i: uint;
begin
//DevPresent:=false;
if(DenyCommunications = false) then begin
if(USB_massive_loading = false) then begin

 if (RS232.Active = false)then
 begin
    RS232.Properties.PortNum  := comport_number;
    RS232.Open;
    RS232.StartListner;
    CloseTimer.Enabled:=false;
    CloseTimer.Interval:=100;
    CloseTimer.Enabled:=true;
 end;
    if (RS232.Active)then
    begin
      DevPresent:=true;

      bytes_to_send:=0;
      i:=0;

      if ((device_serial_0=0) or (device_serial_1=0) or (device_serial_2=0)) then
        bytes_to_send:=bytes_to_send+3;

      if (date_sent_flag=false) then
        bytes_to_send:=bytes_to_send+7;

      bytes_to_send:=bytes_to_send+3; // + запрос текущего фона, версии железа и прошивки

      SetLength(vAns, bytes_to_send);


      if (date_sent_flag=false) then
      begin
        vAns[0]:=$e4; i:=i+1;

        DateTimeToString(formattedDateTime, 'y', Now);
        vAns[i]:=StrToInt(formattedDateTime); i:=i+1;

        DateTimeToString(formattedDateTime, 'm', Now);
        vAns[i]:=StrToInt(formattedDateTime); i:=i+1;

        DateTimeToString(formattedDateTime, 'd', Now);
        vAns[i]:=StrToInt(formattedDateTime); i:=i+1;

        DateTimeToString(formattedDateTime, 'h', Now);
        vAns[i]:=StrToInt(formattedDateTime); i:=i+1;

        DateTimeToString(formattedDateTime, 'n', Now);
        vAns[i]:=StrToInt(formattedDateTime); i:=i+1;

        DateTimeToString(formattedDateTime, 's', Now);
        vAns[i]:=StrToInt(formattedDateTime); i:=i+1;

        date_sent_flag:=true;
      end;

      if ((device_serial_0=0) or (device_serial_1=0) or (device_serial_2=0)) then
      begin
        vAns[i]:= $e0; i:=i+1; // считать серийный номер МК U_ID_0
        vAns[i]:= $e1; i:=i+1; // считать серийный номер МК U_ID_1
        vAns[i]:= $e2; i:=i+1; // считать серийный номер МК U_ID_2
      end;

      vAns[i]:=$d4; i:=i+1; // считать текущие данные

      if(firmware_date='') then
      begin
        vAns[i]:=$e5; i:=i+1; // считать дату прошивки
        vAns[i]:=$e6; i:=i+1; // считать дату прошивки
      end;

      if(About_f.About.Timer2.Enabled = true) then
        vAns[i]:=$34; i:=i+1; // считать данные калибровки

      if Length(vAns) > 0 then RS232.Send(vAns);

    end else begin
      if(DevPresent=true) then
      begin
        DevPresent:=false;
        firmware_date:='';
        date_sent_flag:=false;
        device_serial_0:=0;
        device_serial_1:=0;
        device_serial_2:=0;
        About_f.About.Edit2.Color := clWhite;
      end;
    end;



  end;
end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Timer2Timer(Sender: TObject);
var
  foo: TPoint;
  tick: uint32;
  hour: uint32;
  minute: uint32;
begin
  foo:=Image2.ScreenToClient(Mouse.CursorPos);
  if(foo.X < Image2.Width) and (foo.Y < Image2.Height) and (foo.X > 0) and (foo.Y > 0) then
  begin
    tick:=((foo.X+3) Div 5);
    while tick>0 do
    begin
      if (tick >= 6) then
      begin
       hour:=hour+1;
       tick:=tick-6;
      end
      else
      begin
       minute:=tick*10;
       tick:=0;
      end;
    end;

    if ((((Image2.Width-foo.X) Div 5)>time_offset) or (Combobox1.ItemIndex <> 0)) then begin
       if(geiger_seconds_count>600) then begin
          Label9.Caption:=avg_lang+    IntToStr(((((doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset] + doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset+1]) * geiger_seconds_count) Div 1200)))+   mkr2_lang;
          Label10.Caption:=maxi2_lang+IntToStr(max_fon_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset])+mkr2_lang;

            if(mainfrm.units.Checked = true) then begin
              Label9.Caption:=avg_lang+   Convert_to_usv(((((doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset] + doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset+1] ) * geiger_seconds_count) Div 1200)))+   mkzv2_lang;
              Label10.Caption:=maxi2_lang+Convert_to_usv(max_fon_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset])+mkzv2_lang;
            end;
       end
       else begin
          Label9.Caption:=avg_lang+    IntToStr(((doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset] * geiger_seconds_count) Div 600))+   mkr2_lang;
          Label10.Caption:=maxi2_lang+IntToStr(max_fon_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset])+mkr2_lang;

            if(mainfrm.units.Checked = true) then begin
              Label9.Caption:=avg_lang+   Convert_to_usv(((doze_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset] * geiger_seconds_count) Div 600))+   mkzv2_lang;
              Label10.Caption:=maxi2_lang+Convert_to_usv(max_fon_massive[((Image2.Width-foo.X) Div 5)+(144*(Combobox1.ItemIndex))-time_offset])+mkzv2_lang;
            end;
       end;
    end else begin
      if(mainfrm.units.Checked = true) then
      begin Label9.Caption:=avg2zv_lang;
            Label10.Caption:=maxi3zv_lang;
      end else
      begin Label9.Caption:=avg2_lang;
            Label10.Caption:=maxi3_lang;
      end;
    end;
    Label11.Caption:=time_lang+IntToStr(hour)+hours2_lang+IntToStr(minute)+minutes2_lang;

end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Timer3Timer(Sender: TObject);
var
  vAns: TiaBuf;
  iy: uint32;
begin

if(usb_send_try < 10) then
 begin
   if (address = address_last) and (USB_massive_loading = true) then
   begin
    SetLength(vAns, 1);
    usb_send_try:=usb_send_try+1;
    if Length(vAns) > 0 then RS232.Send(vAns);
   end
   else address_last:=address;
  end
  else
  begin
    address:=0;
    address_last:=0;
    usb_send_try:=0;
    RS232.StopListner;
    RS232.Close;
    DevPresent:= false;
    firmware_date:='';
    date_sent_flag:=false;
    device_serial_0:=0;
    device_serial_1:=0;
    device_serial_2:=0;
    About_f.About.Edit2.Color := clWhite;

    Unit1.Form1.Close;
    USB_massive_loading:=false;

  end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Timer4Timer(Sender: TObject);
var
 AIdHTTP: TIdHTTP;
 reg: TRegistry;
 key: String;
begin
if (DevPresent) then
  begin
    reg := TRegistry.Create;                              // Открываем реестр
    reg.RootKey := HKEY_CURRENT_USER;
    reg.OpenKey('Software\Micron\Ultra-Micron', false);
    key := reg.ReadString('Reg_key');
    reg.CloseKey;                                          // Закрываем раздел
    AIdHTTP := TIdHTTP.Create(nil);
    AIdHTTP.HandleRedirects := true;
    try
      AIdHTTP.Get(  Concat('http://upload.xn--h1aeegel.net/upload.php?id=',key,'&fon=',IntToStr(fon)));
    except
      begin
      end;
    end;
    AIdHTTP.Disconnect;
    AIdHTTP.Free;
  end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.unitsClick(Sender: TObject);
begin
  if(Licensed_state<>true) then
  begin
    mainfrm.units.Checked:= false; // проверка лицензии
    showmessage('Registred device not connected!');
  end;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.AboutBtnClick(Sender: TObject);
begin
try
About.ShowModal;
except
end;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.AquaBtnClick(Sender: TObject);
begin
  tempcol := clAqua;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.OliveBtnClick(Sender: TObject);
begin
  tempcol := clOlive;
  SaveReg;
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.FormDestroy(Sender: TObject);
begin
  RS232.StopListner;
  FreeAndNil(RS232);
end;
// =============================================================================


// =============================================================================
procedure TmainFrm.Draw_massive();
var
 ii: uint32;
 scale_factor: uint32;
 always_multipiller: uint32;
 massive_pointer:uint32;
begin
// граф ИМПУЛЬСОВ

MainFrm.Width:=1148;
  Image2.Picture:= nil;

  Image2.Canvas.Brush.Color := RGB(186, 170, 134);
  Image2.Canvas.Pen.Color := clBlack;
  Image2.Canvas.Rectangle(0,0,Image2.Width, Image2.Height);

  graph_x:=0;
  graph_y:=96;
  always_multipiller:=Image2.Height Div 5;
  scale_factor:=10;

    for ii := 0 to 144 do
    begin
      if ((ii>time_offset) or (Combobox1.ItemIndex <> 0)) then begin
        if((max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]*always_multipiller)>=Image2.Height) then
        begin
          if(scale_factor < (((max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]*always_multipiller) Div Image2.Height)+1)) then
          scale_factor:=((max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]*always_multipiller) Div Image2.Height)+1;

          if(scale_factor = 0) then scale_factor:=1;
        end;
      end;

    end;

    for ii := 0 to 144 do
    begin
      if ((ii>time_offset) or (Combobox1.ItemIndex <> 0)) then begin


         graph_y:= (max_fon_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]                                    * always_multipiller) Div scale_factor;

         if(geiger_seconds_count>600) then begin
          graph_y2:=((((( doze_massive[ii+(144*(Combobox1.ItemIndex))-time_offset] + doze_massive[ii+(144*(Combobox1.ItemIndex))-time_offset + 1] )  * geiger_seconds_count) Div 1200 ))  * always_multipiller) Div scale_factor;
         end
         else begin
          graph_y2:=((( doze_massive[ii+(144*(Combobox1.ItemIndex))-time_offset]  * geiger_seconds_count) Div 600)  * always_multipiller) Div scale_factor;
        end;


        if graph_y=graph_y2 then graph_y2:=graph_y-1;
        Image2.Canvas.Brush.Color :=  RGB(0, 29, 135);
        if (selected_point_massive = ii+(144*(Combobox1.ItemIndex))-time_offset) then Image2.Canvas.Brush.Color :=  RGB(255, 0, 0);
        Image2.Canvas.Brush.Style:= bsSolid;
        Image2.Canvas.Pen.Color := clBlack;
        Image2.Canvas.Rectangle(Image2.Width-graph_x-4, Image2.Height, Image2.Width-graph_x, Image2.Height-graph_y2);

        Image2.Canvas.Brush.Color := clRED;
        Image2.Canvas.Brush.Style:= bsBDiagonal;
        if (selected_point_massive = ii+(144*(Combobox1.ItemIndex))-time_offset) then  Image2.Canvas.Brush.Style:= bsDiagCross;
        Image2.Canvas.Pen.Color := clBlack;
        Image2.Canvas.Rectangle(Image2.Width-graph_x-4, Image2.Height-graph_y2, Image2.Width-graph_x, Image2.Height-graph_y);
      end;
      graph_x:=graph_x+5;
    end;

    graph_y:= (15 * always_multipiller) Div scale_factor; // линия 15 мкр/ч
    Image2.Canvas.Brush.Color := clGREEN;
    Image2.Canvas.Brush.Style:= bsSolid;
    Image2.Canvas.Pen.Color := clGREEN;
    Image2.Canvas.Font.Color:=clGREEN;
    Image2.Canvas.Brush.Style:=bsClear;
    Image2.Canvas.Font.Size:=12;
    if graph_y<=Image2.Height then begin
      Image2.Canvas.Rectangle(Image2.Width, Image2.Height-graph_y, 0, Image2.Height-graph_y-1);
      if(mainfrm.units.Checked = true) then
      begin Image2.Canvas.TextOut(0,Image2.Height-graph_y,'0.15'+mkzv2_lang); end
      else  Image2.Canvas.TextOut(0,Image2.Height-graph_y,'15'+mkr2_lang);
    end;

    graph_y:= (30 * always_multipiller) Div scale_factor; // линия 30 мкр/ч
    Image2.Canvas.Brush.Color := clYELLOW;
    Image2.Canvas.Brush.Style:= bsSolid;
    Image2.Canvas.Pen.Color := clYELLOW;
    Image2.Canvas.Font.Color:=clYELLOW;
    Image2.Canvas.Brush.Style:=bsClear;
    Image2.Canvas.Font.Size:=12;
    if graph_y<=Image2.Height then begin
      Image2.Canvas.Rectangle(Image2.Width, Image2.Height-graph_y, 0, Image2.Height-graph_y-1);
      if(mainfrm.units.Checked = true) then
      begin Image2.Canvas.TextOut(0,Image2.Height-graph_y,'0.30'+mkzv2_lang); end
      else  Image2.Canvas.TextOut(0,Image2.Height-graph_y,'30'+mkr2_lang);
    end;

    graph_y:= (50 * always_multipiller) Div scale_factor; // линия 50 мкр/ч
    Image2.Canvas.Brush.Color := clRED;
    Image2.Canvas.Brush.Style:= bsSolid;
    Image2.Canvas.Pen.Color := clRED;
    Image2.Canvas.Font.Color:=clRED;
    Image2.Canvas.Brush.Style:=bsClear;
    Image2.Canvas.Font.Size:=12;
    if graph_y<=Image2.Height then begin
      Image2.Canvas.Rectangle(Image2.Width, Image2.Height-graph_y, 0, Image2.Height-graph_y-1);
      if(mainfrm.units.Checked = true) then
      begin Image2.Canvas.TextOut(0,Image2.Height-graph_y,'0.50'+mkzv2_lang); end
      else Image2.Canvas.TextOut(0,Image2.Height-graph_y,'50'+mkr2_lang);
    end;

end;
// =============================================================================


//================================================================================================================
procedure TmainFrm.DoOnReceiveEvent(Sender: TObject; const aData: TiaBuf; aCount: Cardinal);
Var
  ia:uint;
  F: Integer;
  cal_pointer: uint;
  eeprom_pointer: uint;
  ss: String;
  vCount: Integer;
  vBufCount: Integer;
  massive_element: UInt32 ;
  vAns: TiaBuf;
  ix : uint32;
  iy : uint32;
  buffer_len: uint32;
  used_len: uint32;
  packet_size: uint32;
  aData_massive_pointer: uint32;
  fBuf_pointer: uint32;
//  StopRS232: Boolean;
  AIdHTTP: TIdHTTP;
  reg: TRegistry;
  key: String;
  data: TIdMultiPartFormDataStream;


begin
//Voltage_level:=0;
packet_size:=7;
aData_massive_pointer:=0;
fBuf_pointer:=0;
//StopRS232:=FALSE;

CloseTimer.Enabled:=false;
CloseTimer.Interval:=1000;
CloseTimer.Enabled:=true;

While used_len<(Length(aData)-1) do begin
//sleep(1);
  // Заполнение массива пакета
   For F := aData_massive_pointer to aData_massive_pointer + packet_size - 1 do
     Begin
       fBuf[fBuf_pointer] := aData[F];
       Inc(fBuf_pointer);
       if F > (Length(aData)-1) then Break;
       used_len:=F;
     end;
   aData_massive_pointer:=used_len+1;
   fBuf_pointer:=0;

     begin
       ss := '';
       For F := 0 To packet_size - 1 do
         ss := ss + IntToHex(fBuf[F],2) + ' ';

//-----------------------------------------------------------------------------------
if (fBuf[0] = $d1) then begin
  Receive_current_data;        // Чтение данных каждые 4 секунды
end;
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
if (fBuf[0] = $d2) then begin // чтение смещения времени

  time_offset_device := (fBuf[1] shl 8)+fBuf[2]; // собираем 2 чара

end;
//-----------------------------------------------------------------------------------

if (fBuf[0] = $f6) then begin // чтение калибровки

  cal_pointer := fBuf[6];


  if(cal_pointer<19)then begin
    geiger_seconds_count:=                      fBuf[1] shl 8;
    geiger_seconds_count:=geiger_seconds_count+ fBuf[2];
    calibration_data[cal_pointer] := Convert_to_usv((fBuf[5] shl 16)+(fBuf[4] shl 8)+fBuf[3]);
  end;

end;

//-----------------------------------------------------------------------------------

if (fBuf[0] = $f7) then begin // чтение данных из EEPROM

  eeprom_pointer := ((fBuf[1] shl 8)+fBuf[2]) div 4;
  EEPROM_DATA[eeprom_pointer] := (fBuf[3] shl 24)+(fBuf[4] shl 16)+(fBuf[5] shl 8)+fBuf[6];

  // Заполнение комбобокса изотопа
  if eeprom_pointer = ($80 div 4) then
    About_f.About.Isotop.ItemIndex:=Main.EEPROM_data[eeprom_pointer];

end;

//-----------------------------------------------------------------------------------
if (fBuf[0] = $e0) then begin // Серийника U_ID_0

  device_serial_0 := (fBuf[4] shl 24)+(fBuf[3] shl 16)+(fBuf[2] shl 8)+fBuf[1]; // собираем 2 чара
  if device_serial_0 >0 then
   if device_serial_1 >0 then
    if device_serial_2 >0 then
      if(fBuf[6]=1) then begin
                  About_f.About.Edit2.Color := clGreen; Licensed_state:=true; end
      else begin  About_f.About.Edit2.Color := clRed;   Licensed_state:=false; end;
end;
//-----------------------------------------------------------------------------------

if (fBuf[0] = $e1) then begin // Серийника U_ID_1

  device_serial_1 := (fBuf[4] shl 24)+(fBuf[3] shl 16)+(fBuf[2] shl 8)+fBuf[1]; // собираем 2 чара
  if device_serial_0 >0 then
   if device_serial_1 >0 then
    if device_serial_2 >0 then
      if(fBuf[6]=1) then begin
                  About_f.About.Edit2.Color := clGreen; Licensed_state:=true; end
      else begin  About_f.About.Edit2.Color := clRed;   Licensed_state:=false; end;
end;
//-----------------------------------------------------------------------------------

if (fBuf[0] = $e2) then begin // Серийника U_ID_2

  device_serial_2 := (fBuf[4] shl 24)+(fBuf[3] shl 16)+(fBuf[2] shl 8)+fBuf[1]; // собираем 2 чара
  if device_serial_0 >0 then
   if device_serial_1 >0 then
    if device_serial_2 >0 then
      if(fBuf[6]=1) then begin
                  About_f.About.Edit2.Color := clGreen; Licensed_state:=true; end
      else begin  About_f.About.Edit2.Color := clRed;   Licensed_state:=false; end;
end;


//-----------------------------------------------------------------------------------
if (fBuf[0] = $e5) then begin // Дата прошивки

  firmware_date:=Char(Ord(fBuf[1]))+
                 Char(Ord(fBuf[2]))+
                 ' '+
                 Char(Ord(fBuf[3]))+
                 Char(Ord(fBuf[4]))+
                 Char(Ord(fBuf[5]))+
                 ' 201'+
                 Char(Ord(fBuf[6]));
  HW_Label.Caption:='Ultra-Micron HW:'+hardware_version+'  FW:'+firmware_date;
//  if(Need_build<>firmware_date) then
//    showmessage('Unsupported device detected! Reload firmeare NOW!');

end;


//-----------------------------------------------------------------------------------
if (fBuf[0] = $e6) then begin // Версия железа

  hardware_version:=Char(Ord(fBuf[1]))+
                    Char(Ord(fBuf[2]))+
                    Char(Ord(fBuf[3]))+
                    Char(Ord(fBuf[4]))+
                    Char(Ord(fBuf[5]));
HW_Label.Caption:='Ultra-Micron HW:'+hardware_version+'  FW:'+firmware_date;
end;


//-----------------------------------------------------------------------------------
if ((fBuf[0] = $f1) or (fBuf[0] = $81))  then begin // загрузка элемента массива максимального фона

  address:=         fBuf[1] shl 8;
  address:=address+ fBuf[2];

//  if(Length(Unit1.Form1.max_fon.Caption)<4) then
    Unit1.Form1.max_fon.Caption:=   IntToStr(address Div 86)+'%';

  if (address < max_address) then begin

    if (fBuf[0] = $f1) then begin
      massive_element:=                 fBuf[3] shl 24;
      massive_element:=massive_element+(fBuf[4] shl 16);
      massive_element:=massive_element+(fBuf[5] shl 8);
      massive_element:=massive_element+ fBuf[6];

      max_fon_massive[address]:=massive_element;
      max_fon_massive_ready[address]:=true;
    end;

    if(fBuf[0] = $81) then begin
      max_fon_massive[address]:=  fBuf[6];
      max_fon_massive[address+1]:=fBuf[5];
      max_fon_massive[address+2]:=fBuf[4];
      max_fon_massive[address+3]:=fBuf[3];
      max_fon_massive_ready[address]:=true;
      max_fon_massive_ready[address+1]:=true;
      max_fon_massive_ready[address+2]:=true;
      max_fon_massive_ready[address+3]:=true;
      address:=address+3;
    end;

  end else begin

    Unit1.Form1.Refresh;


  end;
end;
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
if ((fBuf[0] = $f3) or (fBuf[0] = $83)) then begin // загрузка элемента массива дозы

  address:=         fBuf[1] shl 8;
  address:=address+ fBuf[2];

  massive_element:=                 fBuf[3] shl 24;
  massive_element:=massive_element+(fBuf[4] shl 16);
  massive_element:=massive_element+(fBuf[5] shl 8);
  massive_element:=massive_element+ fBuf[6];


  if (address < max_address) then
  begin
//    if Fix_error_now=false then
//    begin
      Unit1.Form1.impulses.Caption:=   IntToStr(address Div 86)+'%';
//    end else
//    begin
//      if(doze_massive_ready[address]=false) then
//        Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)-1);
//    end;
    doze_massive[address]:=massive_element;
    doze_massive_ready[address]:=true;

    if(fBuf[0] = $83) then begin
      doze_massive[address]:=  fBuf[6];
      doze_massive[address+1]:=fBuf[5];
      doze_massive[address+2]:=fBuf[4];
      doze_massive[address+3]:=fBuf[3];
      doze_massive_ready[address]:=true;
      doze_massive_ready[address+1]:=true;
      doze_massive_ready[address+2]:=true;
      doze_massive_ready[address+3]:=true;
      address:=address+3;
    end;


  end
  else
  begin
    SetLength(vAns, 1);
    vAns[0]:=$39;
//    StopRS232:=TRUE;

    Timer3.Enabled:=false;
    Timer2.Enabled:=true;

    Combobox1.ItemIndex := 0;
//    showmessage(IntToStr(time_offset_device));
    DateTimeToString(formattedDateTime, 'h', IncSecond(myDate, -(4*time_offset_device)));
    time_offset:=StrToInt(formattedDateTime)*60;
    DateTimeToString(formattedDateTime, 'n', IncSecond(myDate, -(4*time_offset_device)));
    time_offset:=time_offset+StrToInt(formattedDateTime);
    time_offset:=144-(time_offset Div 10); //113

    Unit1.Form1.errors.Caption:='0';
    for iy := 0 to max_address-1 do begin
      if(max_fon_massive_ready[iy]=false) then
        Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)+1);
      if(doze_massive_ready[iy]=false)    then
        Unit1.Form1.errors.Caption:=IntToStr(StrToInt(Unit1.Form1.errors.Caption)+1);
    end;

    if(StrToInt(Unit1.Form1.errors.Caption)=0) then
    begin
      USB_massive_loading:=false;

      Unit1.Form1.Refresh;

/////////////////////////////////////////////////////////////////////////////////////
  // Загрузка данных на сервер
      used_len:=(Length(aData)-1); // принудительно завершаем цикл
      MyThread:=TMyThread.Create(False);
      MyThread.Priority:=tpNormal;
/////////////////////////////////////////////////////////////////////////////////////

      Unit1.Form1.Refresh;

      Draw_massive();
      Unit1.Form1.Close;
    end;
  end;

end;
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
if (fBuf[0] = $f5) then begin // загрузка настроек

  geiger_seconds_count:=                      fBuf[1] shl 8;
  geiger_seconds_count:=geiger_seconds_count+ fBuf[2];
end;
//-----------------------------------------------------------------------------------

end;

end;

  if Length(vAns) > 0 then RS232.Send(vAns);

  //if(StopRS232 = TRUE) then
//begin
//  RS232.StopListner;
//  RS232.Close;
//end;

if(USB_massive_loading = false) then
begin
//  RS232.StopListner;
//  RS232.Close;
  if((Voltage_level Div 10) Mod 100)>9 then
  begin
   Voltage.Caption:=voltage_lang+IntToStr(Voltage_level Div 1000)+'.'+IntToStr((Voltage_level Div 10) Mod 100)+' V';
  end
  else
  begin
   Voltage.Caption:=voltage_lang+IntToStr(Voltage_level Div 1000)+'.0'+IntToStr((Voltage_level Div 10) Mod 100)+' V';
  end;
end;
end;
//================================================================================================================


// =============================================================================
procedure TmainFrm.DoOnSendedEvent(Sender: TObject; const aData: TiaBuf;
  aCount: Cardinal);
Var
  F: INteger;
  ss: String;
begin
  ss := '';
  For F := 0 To Length(aData) - 1 do
    ss := ss + IntToHex(aData[F],2) + ' ';

end;


end.
