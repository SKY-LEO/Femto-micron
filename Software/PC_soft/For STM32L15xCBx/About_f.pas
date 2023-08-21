unit About_f;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, pngimage, ExtCtrls, Registry, iaRS232;

type
  TAbout = class(TForm)
    Label1: TLabel;
    Image1: TImage;
    Button1: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit1: TEdit;
    Label6: TLabel;
    Edit2: TEdit;
    Label7: TLabel;
    Timer1: TTimer;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Label8: TLabel;
    Memo1: TMemo;
    Button2: TButton;
    Timer2: TTimer;
    Button3: TButton;
    Na22: TEdit;
    Ti44: TEdit;
    Y88: TEdit;
    Cd109: TEdit;
    Ba133: TEdit;
    Cs137: TEdit;
    Eu152: TEdit;
    Th228: TEdit;
    Am241: TEdit;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Button4: TButton;
    Timer3: TTimer;
    Isotop: TComboBox;
    Изотоп: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  About: TAbout;

implementation

{$R *.dfm}
uses main;

procedure TAbout.Button1Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
begin
try
   if Edit3.Text <> '' then
   if Edit4.Text <> '' then
   if Edit5.Text <> '' then
   if Edit6.Text <> '' then
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Properties.PortNum  := comport_number;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;

        mainFrm.CloseTimer.Enabled:=false;
        mainFrm.CloseTimer.interval:=100;
        mainFrm.CloseTimer.Enabled:=true;
      end;

        if (mainFrm.RS232.Active)then
        begin
         //DevPresent:=true;
         SetLength(vAns, 5);

         vAns[0]:=$e3;

         tmp:=        StrToInt('$'+Copy(Edit3.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit3.Text, 3, 2));
         vAns[1]:=tmp-StrToInt('$'+Copy(Edit3.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit4.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit4.Text, 3, 2));
         vAns[2]:=tmp-StrToInt('$'+Copy(Edit4.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit5.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit5.Text, 3, 2));
         vAns[3]:=tmp-StrToInt('$'+Copy(Edit5.Text, 1, 2));

         tmp:=        StrToInt('$'+Copy(Edit6.Text, 5, 3));
         tmp:=    tmp-StrToInt('$'+Copy(Edit6.Text, 3, 2));
         vAns[4]:=tmp-StrToInt('$'+Copy(Edit6.Text, 1, 2));

         mainFrm.RS232.Send(vAns);
        end
        else
        begin
          showmessage('Error 491: Port blocked');
        end;
    end;
//    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;

  reg := TRegistry.Create;                               // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;                      // Для текущего пользователя
  reg.OpenKey('Software\Micron\Ultra-Micron', true); // Открываем раздел
  reg.WriteString('Reg_key', Edit1.Text);
  reg.CloseKey;                                          // Закрываем раздел
  reg.Free;
  About.Close;
end;


procedure TAbout.Button2Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
  ix: uint32;
begin
About_f.About.Timer2.Enabled := true;

 for ix := 0 to 18 do begin
  calibration_data[ix]:='';
 end;


try
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Properties.PortNum  := comport_number;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;

        mainFrm.CloseTimer.Enabled:=false;
        mainFrm.CloseTimer.interval:=100;
        mainFrm.CloseTimer.Enabled:=true;
      end;

        if (mainFrm.RS232.Active)then
        begin
         //DevPresent:=true;
         SetLength(vAns, 1);

         vAns[0]:=$35;
         mainFrm.RS232.Send(vAns);
        end
        else
        begin
          showmessage('Error 491: Port blocked');
        end;
    end;
//    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;

end;

procedure TAbout.Button3Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
  ix: uint32;
begin
About_f.About.Timer2.Enabled := false;

 for ix := 0 to 18 do begin
  calibration_data[ix]:='';
 end;


try
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Close;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;

        mainFrm.CloseTimer.Enabled:=false;
        mainFrm.CloseTimer.interval:=100;
        mainFrm.CloseTimer.Enabled:=true;
      end;

        if (mainFrm.RS232.Active)then
        begin
         //DevPresent:=true;
         SetLength(vAns, 1);

         vAns[0]:=$36;
         mainFrm.RS232.Send(vAns);
         ShowMessage('Требуется перезагрузка программы');
         needexit := true; // вежливо просим свалить из памяти
        end
        else
        begin
          showmessage('Error 491: Port blocked');
        end;
    end;
//    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;


end;

procedure TAbout.Button4Click(Sender: TObject);
var
  reg: TRegistry;
  vAns: TiaBuf;
  tmp: uint32;
  ix: uint32;
begin

try
    begin
      if (mainFrm.RS232.Active = false) then
       begin
        mainFrm.RS232.Properties.PortNum  := comport_number;
        mainFrm.RS232.Open;
        mainFrm.RS232.StartListner;

        mainFrm.CloseTimer.Enabled:=false;
        mainFrm.CloseTimer.interval:=100;
        mainFrm.CloseTimer.Enabled:=true;
      end;

        if (mainFrm.RS232.Active)then
        begin

        // Сохраниение данных в EEPROM

        // Выбранный изотоп
        if ((About_f.About.Isotop.ItemIndex <> Main.EEPROM_data[$80 div 4]) and (About_f.About.Isotop.ItemIndex <> -1)) then
        begin
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$80; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= About_f.About.Isotop.ItemIndex         and $ff;
            vAns[4]:=(About_f.About.Isotop.ItemIndex shr 8)  and $ff;
            vAns[5]:=(About_f.About.Isotop.ItemIndex shr 16) and $ff;
            vAns[6]:=(About_f.About.Isotop.ItemIndex shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Cs-137
        if ( (About_f.About.Cs137.Text <> Main.EEPROM_data[$84 div 4].Tostring()) and (About_f.About.Cs137.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Cs137.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Cs137.Text:=ix.ToString();

            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$84; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Cs137.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Cs137.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Cs137.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Cs137.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Eu-152
        if ( (About_f.About.Eu152.Text <> Main.EEPROM_data[$88 div 4].Tostring()) and (About_f.About.Eu152.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Eu152.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Eu152.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$88; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Eu152.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Eu152.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Eu152.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Eu152.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;


        // Na-22
        if ( (About_f.About.Na22.Text <> Main.EEPROM_data[$8C div 4].Tostring()) and (About_f.About.Na22.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Na22.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Na22.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$8C; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Na22.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Na22.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Na22.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Na22.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Cd-109
        if ( (About_f.About.Cd109.Text <> Main.EEPROM_data[$90 div 4].Tostring()) and (About_f.About.Cd109.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Cd109.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Cd109.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$90; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Cd109.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Cd109.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Cd109.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Cd109.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Am-241
        if ( (About_f.About.Am241.Text <> Main.EEPROM_data[$C0 div 4].Tostring()) and (About_f.About.Am241.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Am241.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Am241.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$C0; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Am241.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Am241.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Am241.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Am241.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Y-88
        if ( (About_f.About.Y88.Text <> Main.EEPROM_data[$C8 div 4].Tostring()) and (About_f.About.Y88.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Y88.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Y88.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$C8; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Y88.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Y88.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Y88.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Y88.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Ti-44
        if ( (About_f.About.Ti44.Text <> Main.EEPROM_data[$D0 div 4].Tostring()) and (About_f.About.Ti44.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Ti44.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Ti44.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$D0; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Ti44.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Ti44.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Ti44.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Ti44.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Ba-133
        if ( (About_f.About.Ba133.Text <> Main.EEPROM_data[$D8 div 4].Tostring()) and (About_f.About.Ba133.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Ba133.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Ba133.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$D8; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Ba133.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Ba133.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Ba133.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Ba133.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Th-228
        if ( (About_f.About.Th228.Text <> Main.EEPROM_data[$E0 div 4].Tostring()) and (About_f.About.Th228.Text <> '0')) then
        begin
            ix:=StrToInt(About_f.About.Th228.Text);
            ix:=(ix div 4) * 4;
            About_f.About.Th228.Text:=ix.ToString();
            SetLength(vAns, 7);
            vAns[0]:=$37;
            vAns[1]:=$E0; // Адрес
            vAns[2]:=$00; // Адрес
            vAns[3]:= StrToInt(About_f.About.Th228.Text)         and $ff;
            vAns[4]:=(StrToInt(About_f.About.Th228.Text) shr 8)  and $ff;
            vAns[5]:=(StrToInt(About_f.About.Th228.Text) shr 16) and $ff;
            vAns[6]:=(StrToInt(About_f.About.Th228.Text) shr 24) and $ff;
            mainFrm.RS232.Send(vAns);
            sleep(100);
        end;

        // Загрузка данных из EEPROM
           for ix := 0 to 99 do begin
            Main.EEPROM_data[ix]:=0;
           end;

          About_f.About.Na22.Text:= '0';
          About_f.About.Ti44.Text:= '0';
          About_f.About.Y88.Text:=  '0';
          About_f.About.Cd109.Text:='0';
          About_f.About.Ba133.Text:='0';
          About_f.About.Cs137.Text:='0';
          About_f.About.Eu152.Text:='0';
          About_f.About.Th228.Text:='0';
          About_f.About.Am241.Text:='0';

          SetLength(vAns, 1);
          vAns[0]:=$38;
          mainFrm.RS232.Send(vAns);
        end
        else
        begin
          showmessage('Error 491: Port blocked');
        end;
    end;
//    end;
except
  on Exception : EConvertError do
    sleep(100);
  end;

end;

procedure TAbout.FormCreate(Sender: TObject);
var
  reg: TRegistry;
begin

  reg := TRegistry.Create;                              // Открываем реестр
  reg.RootKey := HKEY_CURRENT_USER;
  reg.OpenKey('Software\Micron\Ultra-Micron', true); // Открываем раздел
  Edit1.Text := reg.ReadString('Reg_key');
  reg.CloseKey;                                          // Закрываем раздел
end;

procedure TAbout.Timer1Timer(Sender: TObject);
begin
 About_f.About.Edit2.Text := IntToHex(device_serial_0,8)+ ' ' +IntToHex(device_serial_1,8)+ ' ' +IntToHex(device_serial_2,8);
end;

procedure TAbout.Timer2Timer(Sender: TObject);
var
 ix: uint32;
begin

 About_f.About.Memo1.Lines.Clear;
 About_f.About.Memo1.Lines.Add('Время в настройках '+Main.geiger_seconds_count.ToString()+', массив данных:');
 for ix := 0 to 18 do begin
  if (calibration_data[ix] <> '') then
  begin
   About_f.About.Memo1.Lines.Add(calibration_data[ix]);
  end
   else
   begin
     About_f.About.Memo1.Lines.Add('***');
   end;
 end;

  if (calibration_data[18] <> '') then
  begin
   About_f.About.Timer2.Enabled := false;
  end;

  end;

procedure TAbout.Timer3Timer(Sender: TObject);
begin

if ( About_f.About.Cs137.Text = '0' ) then
     About_f.About.Cs137.Text:=Main.EEPROM_data[$84 div 4].Tostring();

if ( About_f.About.Eu152.Text = '0' ) then
     About_f.About.Eu152.Text:=Main.EEPROM_data[$88 div 4].Tostring();

if ( About_f.About.Na22.Text = '0' ) then
     About_f.About.Na22.Text:=Main.EEPROM_data[$8C div 4].Tostring();

if ( About_f.About.Cd109.Text = '0' ) then
     About_f.About.Cd109.Text:=Main.EEPROM_data[$90 div 4].Tostring();

if ( About_f.About.Am241.Text = '0' ) then
     About_f.About.Am241.Text:=Main.EEPROM_data[$C0 div 4].Tostring();

if ( About_f.About.Y88.Text = '0' ) then
     About_f.About.Y88.Text:=Main.EEPROM_data[$C8 div 4].Tostring();

if ( About_f.About.Ti44.Text = '0' ) then
     About_f.About.Ti44.Text:=Main.EEPROM_data[$D0 div 4].Tostring();

if ( About_f.About.Ba133.Text = '0' ) then
     About_f.About.Ba133.Text:=Main.EEPROM_data[$D8 div 4].Tostring();

if ( About_f.About.Th228.Text = '0' ) then
     About_f.About.Th228.Text:=Main.EEPROM_data[$E0 div 4].Tostring();

if ( About_f.About.Isotop.Items.Count = 0 ) then begin
  About_f.About.Isotop.AddItem('Cs-137',nil);
  About_f.About.Isotop.AddItem('Eu-152',nil);
  About_f.About.Isotop.AddItem('Na-22' ,nil);
  About_f.About.Isotop.AddItem('Cd-109',nil);
  About_f.About.Isotop.AddItem('Am-241',nil);
  About_f.About.Isotop.AddItem('Y-88',nil);
  About_f.About.Isotop.AddItem('Ti-44',nil);
  About_f.About.Isotop.AddItem('Ba-133',nil);
  About_f.About.Isotop.AddItem('Th-228',nil);
end;




end;

end.
