unit Serials;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Button1: TButton;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
input:uint32;
tmp:uint32;
result1:uint32;
result2:uint32;
result3:uint32;
Str:String;

begin
//input:=StrToInt('$'+Copy(Edit1.Text, 1, 8));
Str:='';
Edit2.Text:=('$'+Copy(Edit1.Text, 1, 8));
Edit3.Text:=('$'+Copy(Edit1.Text, 10, 8));
Edit4.Text:=('$'+Copy(Edit1.Text, 19, 8));

input:=      StrToInt(Edit2.Text);
input:=input+StrToInt(Edit3.Text);
input:=input+StrToInt(Edit4.Text);
Edit6.Text:=IntToHex(input,4);

result1:=Random(255);
result2:=Random(255);
tmp:=StrToInt('$'+Copy(IntToHex(input,4),1,2));
result3:=tmp+result1+result2;
Str:=Str+IntToHex(result1,2)+IntToHex(result2,2)+IntToHex(result3,3)+' ';

result1:=Random(255);
result2:=Random(255);
tmp:=StrToInt('$'+Copy(IntToHex(input,4),3,2));
result3:=tmp+result1+result2;
Str:=Str+IntToHex(result1,2)+IntToHex(result2,2)+IntToHex(result3,3)+' ';

result1:=Random(255);
result2:=Random(255);
tmp:=StrToInt('$'+Copy(IntToHex(input,4),5,2));
result3:=tmp+result1+result2;
Str:=Str+IntToHex(result1,2)+IntToHex(result2,2)+IntToHex(result3,3)+' ';

result1:=Random(255);
result2:=Random(255);
tmp:=StrToInt('$'+Copy(IntToHex(input,4),7,2));
result3:=tmp+result1+result2;
Str:=Str+IntToHex(result1,2)+IntToHex(result2,2)+IntToHex(result3,3);


Edit5.Text:=Str;
//Edit5.Text:=Copy(IntToHex(input,4),3,2);
//Edit5.Text:=Copy(IntToHex(input,4),5,2);
//Edit5.Text:=Copy(IntToHex(input,4),7,2);

sleep(100);
end;

end.
