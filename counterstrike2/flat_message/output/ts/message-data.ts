// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class MessageData implements flatbuffers.IUnpackableObject<MessageDataT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):MessageData {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

username(index: number):number|null {
    return this.bb!.readInt8(this.bb_pos + 0 + index);
}

message(index: number):number|null {
    return this.bb!.readInt8(this.bb_pos + 32 + index);
}

sticky():boolean {
  return !!this.bb!.readInt8(this.bb_pos + 64);
}

mutate_sticky(value:boolean):boolean {
  this.bb!.writeInt8(this.bb_pos + 64, value);
  return true;
}

static sizeOf():number {
  return 65;
}

static createMessageData(builder:flatbuffers.Builder, username: number[]|null, message: number[]|null, sticky: boolean):flatbuffers.Offset {
  builder.prep(1, 65);
  builder.writeInt8(Number(Boolean(sticky)));

  for (let i = 31; i >= 0; --i) {
    builder.writeInt8((message?.[i] ?? 0));

  }


  for (let i = 31; i >= 0; --i) {
    builder.writeInt8((username?.[i] ?? 0));

  }

  return builder.offset();
}


unpack(): MessageDataT {
  return new MessageDataT(
    this.bb!.createScalarList<number>(this.username.bind(this), 32),
    this.bb!.createScalarList<number>(this.message.bind(this), 32),
    this.sticky()
  );
}


unpackTo(_o: MessageDataT): void {
  _o.username = this.bb!.createScalarList<number>(this.username.bind(this), 32);
  _o.message = this.bb!.createScalarList<number>(this.message.bind(this), 32);
  _o.sticky = this.sticky();
}
}

export class MessageDataT implements flatbuffers.IGeneratedObject {
constructor(
  public username: (number)[] = [],
  public message: (number)[] = [],
  public sticky: boolean = false
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  return MessageData.createMessageData(builder,
    this.username,
    this.message,
    this.sticky
  );
}
}