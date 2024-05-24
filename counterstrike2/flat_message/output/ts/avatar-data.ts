// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class AvatarData implements flatbuffers.IUnpackableObject<AvatarDataT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):AvatarData {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsAvatarData(bb:flatbuffers.ByteBuffer, obj?:AvatarData):AvatarData {
  return (obj || new AvatarData()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsAvatarData(bb:flatbuffers.ByteBuffer, obj?:AvatarData):AvatarData {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new AvatarData()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

username():string|null
username(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
username(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

data(index: number):number|null {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? this.bb!.readInt8(this.bb!.__vector(this.bb_pos + offset) + index) : 0;
}

dataLength():number {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? this.bb!.__vector_len(this.bb_pos + offset) : 0;
}

dataArray():Int8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? new Int8Array(this.bb!.bytes().buffer, this.bb!.bytes().byteOffset + this.bb!.__vector(this.bb_pos + offset), this.bb!.__vector_len(this.bb_pos + offset)) : null;
}

static startAvatarData(builder:flatbuffers.Builder) {
  builder.startObject(2);
}

static addUsername(builder:flatbuffers.Builder, usernameOffset:flatbuffers.Offset) {
  builder.addFieldOffset(0, usernameOffset, 0);
}

static addData(builder:flatbuffers.Builder, dataOffset:flatbuffers.Offset) {
  builder.addFieldOffset(1, dataOffset, 0);
}

static createDataVector(builder:flatbuffers.Builder, data:number[]|Int8Array):flatbuffers.Offset;
/**
 * @deprecated This Uint8Array overload will be removed in the future.
 */
static createDataVector(builder:flatbuffers.Builder, data:number[]|Uint8Array):flatbuffers.Offset;
static createDataVector(builder:flatbuffers.Builder, data:number[]|Int8Array|Uint8Array):flatbuffers.Offset {
  builder.startVector(1, data.length, 1);
  for (let i = data.length - 1; i >= 0; i--) {
    builder.addInt8(data[i]!);
  }
  return builder.endVector();
}

static startDataVector(builder:flatbuffers.Builder, numElems:number) {
  builder.startVector(1, numElems, 1);
}

static endAvatarData(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createAvatarData(builder:flatbuffers.Builder, usernameOffset:flatbuffers.Offset, dataOffset:flatbuffers.Offset):flatbuffers.Offset {
  AvatarData.startAvatarData(builder);
  AvatarData.addUsername(builder, usernameOffset);
  AvatarData.addData(builder, dataOffset);
  return AvatarData.endAvatarData(builder);
}

unpack(): AvatarDataT {
  return new AvatarDataT(
    this.username(),
    this.bb!.createScalarList<number>(this.data.bind(this), this.dataLength())
  );
}


unpackTo(_o: AvatarDataT): void {
  _o.username = this.username();
  _o.data = this.bb!.createScalarList<number>(this.data.bind(this), this.dataLength());
}
}

export class AvatarDataT implements flatbuffers.IGeneratedObject {
constructor(
  public username: string|Uint8Array|null = null,
  public data: (number)[] = []
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  const username = (this.username !== null ? builder.createString(this.username!) : 0);
  const data = AvatarData.createDataVector(builder, this.data);

  return AvatarData.createAvatarData(builder,
    username,
    data
  );
}
}
