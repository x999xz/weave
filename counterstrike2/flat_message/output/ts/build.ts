// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class Build implements flatbuffers.IUnpackableObject<BuildT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):Build {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsBuild(bb:flatbuffers.ByteBuffer, obj?:Build):Build {
  return (obj || new Build()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsBuild(bb:flatbuffers.ByteBuffer, obj?:Build):Build {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new Build()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

build():string|null
build(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
build(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

subTime():bigint {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? this.bb!.readUint64(this.bb_pos + offset) : BigInt('0');
}

mutate_sub_time(value:bigint):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 6);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeUint64(this.bb_pos + offset, value);
  return true;
}

process():string|null
process(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
process(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 8);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

command():string|null
command(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
command(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 10);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

id():number {
  const offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_id(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 12);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

static startBuild(builder:flatbuffers.Builder) {
  builder.startObject(5);
}

static addBuild(builder:flatbuffers.Builder, buildOffset:flatbuffers.Offset) {
  builder.addFieldOffset(0, buildOffset, 0);
}

static addSubTime(builder:flatbuffers.Builder, subTime:bigint) {
  builder.addFieldInt64(1, subTime, BigInt('0'));
}

static addProcess(builder:flatbuffers.Builder, processOffset:flatbuffers.Offset) {
  builder.addFieldOffset(2, processOffset, 0);
}

static addCommand(builder:flatbuffers.Builder, commandOffset:flatbuffers.Offset) {
  builder.addFieldOffset(3, commandOffset, 0);
}

static addId(builder:flatbuffers.Builder, id:number) {
  builder.addFieldInt32(4, id, 0);
}

static endBuild(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createBuild(builder:flatbuffers.Builder, buildOffset:flatbuffers.Offset, subTime:bigint, processOffset:flatbuffers.Offset, commandOffset:flatbuffers.Offset, id:number):flatbuffers.Offset {
  Build.startBuild(builder);
  Build.addBuild(builder, buildOffset);
  Build.addSubTime(builder, subTime);
  Build.addProcess(builder, processOffset);
  Build.addCommand(builder, commandOffset);
  Build.addId(builder, id);
  return Build.endBuild(builder);
}

unpack(): BuildT {
  return new BuildT(
    this.build(),
    this.subTime(),
    this.process(),
    this.command(),
    this.id()
  );
}


unpackTo(_o: BuildT): void {
  _o.build = this.build();
  _o.subTime = this.subTime();
  _o.process = this.process();
  _o.command = this.command();
  _o.id = this.id();
}
}

export class BuildT implements flatbuffers.IGeneratedObject {
constructor(
  public build: string|Uint8Array|null = null,
  public subTime: bigint = BigInt('0'),
  public process: string|Uint8Array|null = null,
  public command: string|Uint8Array|null = null,
  public id: number = 0
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  const build = (this.build !== null ? builder.createString(this.build!) : 0);
  const process = (this.process !== null ? builder.createString(this.process!) : 0);
  const command = (this.command !== null ? builder.createString(this.command!) : 0);

  return Build.createBuild(builder,
    build,
    this.subTime,
    process,
    command,
    this.id
  );
}
}
