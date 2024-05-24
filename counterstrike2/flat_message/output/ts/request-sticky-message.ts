// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class RequestStickyMessage implements flatbuffers.IUnpackableObject<RequestStickyMessageT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):RequestStickyMessage {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsRequestStickyMessage(bb:flatbuffers.ByteBuffer, obj?:RequestStickyMessage):RequestStickyMessage {
  return (obj || new RequestStickyMessage()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsRequestStickyMessage(bb:flatbuffers.ByteBuffer, obj?:RequestStickyMessage):RequestStickyMessage {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new RequestStickyMessage()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

index():number {
  const offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_index(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 4);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

sticky():boolean {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? !!this.bb!.readInt8(this.bb_pos + offset) : false;
}

mutate_sticky(value:boolean):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 6);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt8(this.bb_pos + offset, +value);
  return true;
}

static startRequestStickyMessage(builder:flatbuffers.Builder) {
  builder.startObject(2);
}

static addIndex(builder:flatbuffers.Builder, index:number) {
  builder.addFieldInt32(0, index, 0);
}

static addSticky(builder:flatbuffers.Builder, sticky:boolean) {
  builder.addFieldInt8(1, +sticky, +false);
}

static endRequestStickyMessage(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createRequestStickyMessage(builder:flatbuffers.Builder, index:number, sticky:boolean):flatbuffers.Offset {
  RequestStickyMessage.startRequestStickyMessage(builder);
  RequestStickyMessage.addIndex(builder, index);
  RequestStickyMessage.addSticky(builder, sticky);
  return RequestStickyMessage.endRequestStickyMessage(builder);
}

unpack(): RequestStickyMessageT {
  return new RequestStickyMessageT(
    this.index(),
    this.sticky()
  );
}


unpackTo(_o: RequestStickyMessageT): void {
  _o.index = this.index();
  _o.sticky = this.sticky();
}
}

export class RequestStickyMessageT implements flatbuffers.IGeneratedObject {
constructor(
  public index: number = 0,
  public sticky: boolean = false
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  return RequestStickyMessage.createRequestStickyMessage(builder,
    this.index,
    this.sticky
  );
}
}
